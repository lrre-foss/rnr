#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/GUI/SelectionBox.hpp>
#include <pugixml.hpp>

namespace RNR
{
    World::World(Ogre::Root* ogre, Ogre::SceneManager* ogreSceneManager)
    {
        Instance::setWorld(this);

        m_ogreRoot = ogre;
        m_ogreSceneManager = ogreSceneManager;
        m_datamodel = new Instance();
        m_datamodel->setName("DataModel");
        m_workspace = new Workspace();
        m_workspace->setParent(m_datamodel);

        m_tmb = new TopMenuBar();
    }

    World::~World()
    {
        //
    }

    void World::xmlAddItem(pugi::xml_node node, Instance* parent)
    {
        bool skip = false;
        Instance* instance;
        pugi::xml_attribute class_attr = node.attribute("class");

        if(class_attr.as_string() == std::string("Part"))
        {
            instance = new PartInstance();
        }
        else if(class_attr.as_string() == std::string("Workspace"))
        {
            instance = m_workspace;
        } 
        else if(class_attr.as_string() == std::string("Camera"))
        {
            instance = new Camera();
        } 
        else if(class_attr.as_string() == std::string("Model")) 
        {
            instance = new ModelInstance();
        } 
        else
        {
            instance = new Instance();
        }

        if(!skip)
        {
            pugi::xml_attribute referent = node.attribute("referent");
            if(!referent.empty())
                m_refs[referent.as_string()] = instance;
            WorldUndeserialized s;
            s.instance = instance;
            s.node = node;
            m_undeserialized.push(s);
            instance->setParent(parent);
        }

        for(pugi::xml_node item = node.child("Item"); item; item = item.next_sibling("Item"))
        {
            xmlAddItem(item, instance);
        }
        
        if(class_attr.as_string() == std::string("Model")) 
        {
            ((ModelInstance*)instance)->build();
        } 
    }

    void World::load(char* path)
    {
        m_refs.clear();
        
        pugi::xml_document rbxl_doc;
        pugi::xml_parse_result result = rbxl_doc.load_file(path);
        if(result)
        {
            printf("World::load: XML parsed without errors\n");

            pugi::xml_node root = rbxl_doc.child("roblox");
            for(pugi::xml_node item = root.child("Item"); item; item = item.next_sibling("Item"))
            {
                xmlAddItem(item, m_datamodel);
            }
            while(!m_undeserialized.empty())
            {
                WorldUndeserialized s = m_undeserialized.top();
                m_undeserialized.pop();

                pugi::xml_node props = s.node.child("Properties");
                for(pugi::xml_node prop : props.children())
                {
                    s.instance->deserializeXmlProperty(prop);
                }

                if(s.instance->getClassName() == "Model")
                {
                    ModelInstance* m = (ModelInstance*)s.instance;
                    m->build();
                }
            }
        }
        else
        {
            printf("World::load: XML parsed with errors, description '%s', offset %i\n", result.description(), result.offset);
        }
        m_workspace->build();
    }

    void World::preStep()
    {
        //
    }

    double World::step(float timestep)
    {
        return 0.0;
    }

    void World::update()
    {
        m_workspace->buildGeom();
    }
}