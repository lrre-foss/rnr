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

        load("/home/caesium/Downloads/Telegram Desktop/Destroy-History-1.rbxl");
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
        printf("World::xmlAddItem: adding class %s\n", class_attr.as_string());

        if(class_attr.as_string() == std::string("Part"))
        {
            instance = new PartInstance();
        }
        else if(class_attr.as_string() == std::string("Workspace"))
        {
            instance = m_workspace;
        } 
        else if(class_attr.as_string() == std::string("Model")) 
        {
            instance = new ModelInstance();
        } 
        else
        {
            printf("World::xmlAddItem: adding unknown class\n");
            instance = new Instance();
        }

        if(!skip)
        {
            pugi::xml_node props = node.child("Properties");
            for(pugi::xml_node prop : props.children())
                instance->deserializeXmlProperty(prop);
            instance->setParent(parent);
        }

        for(pugi::xml_node item = node.child("Item"); item; item = item.next_sibling("Item"))
        {
            xmlAddItem(item, instance);
        }
    }

    void World::load(char* path)
    {
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