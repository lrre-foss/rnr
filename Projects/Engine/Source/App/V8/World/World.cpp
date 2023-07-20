#include <App/V8/World/World.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Lighting.hpp>
#include <App/GUI/SelectionBox.hpp>
#include <App/Humanoid/Humanoid.hpp>
#include <App/InputManager.hpp>
#include <Network/Player.hpp>
#include <stdexcept>
#include <pugixml.hpp>

namespace RNR
{
    World::World(Ogre::Root* ogre, Ogre::SceneManager* ogreSceneManager)
    {
        Instance::setWorld(this);

        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
        m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

        m_inputManager = 0;

        m_instanceFactory = new InstanceFactory();

        m_instanceFactory->registerInstance("Camera", InstanceFactory::instanceBuilder<Camera>);
        m_instanceFactory->registerInstance("Model", InstanceFactory::instanceBuilder<ModelInstance>);
        m_instanceFactory->registerInstance("SelectionBox", InstanceFactory::instanceBuilder<SelectionBox>);
        m_instanceFactory->registerInstance("Part", InstanceFactory::instanceBuilder<PartInstance>);
        m_instanceFactory->registerInstance("Workspace", InstanceFactory::instanceBuilder<Workspace>);
        m_instanceFactory->registerInstance("Humanoid", InstanceFactory::instanceBuilder<Humanoid>);
        m_instanceFactory->registerInstance("RunService", InstanceFactory::instanceBuilder<RunService>);
        m_instanceFactory->registerInstance("Players", InstanceFactory::instanceBuilder<Players>);
        m_instanceFactory->registerInstance("Player", InstanceFactory::instanceBuilder<Player>);
        m_instanceFactory->registerInstance("Lighting", InstanceFactory::instanceBuilder<Lighting>);

        m_ogreRoot = ogre;
        m_ogreSceneManager = ogreSceneManager;
        m_datamodel = new DataModel();
        m_datamodel->setName("DataModel");
        m_workspace = (Workspace*)m_datamodel->getService("Workspace");
        m_runService = (RunService*)m_datamodel->getService("RunService");
        m_players = (Players*)m_datamodel->getService("Players");

        m_tmb = new TopMenuBar(this);

        Camera* start_cam = new Camera();
        start_cam->setParent(m_workspace);
        m_workspace->setCurrentCamera(start_cam);
    }

    World::~World()
    {
        //
    }

    void World::xmlAddItem(pugi::xml_node node, Instance* parent)
    {
        pugi::xml_attribute class_attr = node.attribute("class");

        Instance* instance;

        try{
            if(parent == m_datamodel && m_datamodel->findFirstChildOfType(class_attr.as_string()))
                instance = m_datamodel->findFirstChildOfType(class_attr.as_string());
            else
            {
                std::string class_name = class_attr.value();
                instance = m_instanceFactory->build(class_name);
            }
        }
        catch(std::runtime_error e)
        {
            printf("World::xmlAddItem: InstanceFactory::build failed  '%s'\n", e.what());
            return;
        }

        pugi::xml_attribute referent = node.attribute("referent");
        if(!referent.empty())
            m_refs[referent.as_string()] = instance;
        WorldUndeserialized s;
        s.instance = instance;
        s.parent = parent;
        s.node = node;
        m_undeserialized.push(s);

        for(pugi::xml_node item = node.child("Item"); item; item = item.next_sibling("Item"))
            xmlAddItem(item, instance);
    }

    void World::load(char* path)
    {
        m_refs.clear();

        Camera* old_camera = m_workspace->getCurrentCamera();
        if(old_camera)
        {
            m_workspace->setCurrentCamera(0);
            old_camera->setParent(NULL);
        }

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

                s.instance->setParent(s.parent);

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
        if(m_inputManager)
            m_inputManager->frame();
        m_tmb->frame();
    }

    double World::step(float timestep)
    {
        if(m_runService && m_runService->getRunning())
        {
            m_runService->step(timestep);
            m_dynamicsWorld->stepSimulation(timestep);
        }
        m_lastDelta = timestep;
        return 0.0;
    }

    void World::update()
    {
        m_workspace->buildGeom();
    }
}