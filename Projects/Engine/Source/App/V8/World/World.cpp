#include <App/V8/World/World.hpp>
#include <App/V8/World/JointsService.hpp>
#include <App/V8/Tree/InstanceFactory.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Lighting.hpp>
#include <App/GUI/SelectionBox.hpp>
#include <App/Humanoid/Humanoid.hpp>
#include <App/InputManager.hpp>
#include <Network/Player.hpp>
#include <stdexcept>
#include <pugixml.hpp>
#include <Helpers/Bullet.hpp>

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
        m_dynamicsWorld->setGravity(btVector3(0, -64, 0));

        m_inputManager = 0;
        m_loadListener = 0;

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
        m_instanceFactory->registerInstance("JointsService", InstanceFactory::instanceBuilder<JointsService>);

        m_ogreRoot = ogre;
        m_ogreSceneManager = ogreSceneManager;
        m_datamodel = new DataModel();
        m_datamodel->setName("DataModel");
        m_workspace = (Workspace*)m_datamodel->getService("Workspace");
        m_runService = (RunService*)m_datamodel->getService("RunService");
        m_players = (Players*)m_datamodel->getService("Players");

        m_joints = new JointsService();
        m_joints->setParent(m_datamodel);

        m_runPhysics = true;
        m_ngine = new ComPlicitNgine(this);
        m_tmb = new TopMenuBar(this);

        Camera* start_cam = new Camera();
        start_cam->setParent(m_workspace);
        m_workspace->setCurrentCamera(start_cam);

        PartInstance* baseplate = new PartInstance();
        baseplate->setName("Baseplate");
        baseplate->getCFrame().setPosition(Ogre::Vector3(5, -64, 5));
        baseplate->setSize(Ogre::Vector3(512, 1, 512));
        baseplate->setBrickColor(2);
        baseplate->setAnchored(true);
        baseplate->updateSurfaces();
        baseplate->setParent(m_workspace);
    }

    World::~World()
    {
        m_runPhysics = false;
        delete m_ngine;
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

    void World::load(char* path, ILoadListener* loadListener)
    {
        m_loadState = LOADING_DATAMODEL;
        m_loadListener = loadListener;
        m_refs.clear();

        JointsService* joints = (JointsService*)m_datamodel->getService("JointsService");
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

            int children = 0;            
            pugi::xml_node root = rbxl_doc.child("roblox");
            for(pugi::xml_node item = root.child("Item"); item; item = item.next_sibling("Item"))
            {
                m_loadState = LOADING_DATAMODEL;
                m_loadProgress = children;
                m_maxLoadProgress = children+1;
                children++;
                if(loadListener)
                    loadListener->updateWorldLoad();
                xmlAddItem(item, m_datamodel);
            }
            int undeserialized_size = m_undeserialized.size();
            while(!m_undeserialized.empty())
            {
                WorldUndeserialized s = m_undeserialized.top();
                m_undeserialized.pop();
                
                m_loadState = LOADING_DATAMODEL_PROPERTIES;
                m_maxLoadProgress = undeserialized_size;
                m_loadProgress = undeserialized_size-m_undeserialized.size();
                if(loadListener)
                    loadListener->updateWorldLoad();

                pugi::xml_node props = s.node.child("Properties");
                for(pugi::xml_node prop : props.children())
                {
                    s.instance->deserializeXmlProperty(prop);
                }

                s.instance->setParent(s.parent);

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
            m_loadState = LOADING_FINISHED;
            m_loadListener = 0;
        }        
        m_workspace->build();
        m_loadState = LOADING_MAKEJOINTS;
        m_workspace->makeJoints();
        m_loadState = LOADING_FINISHED;
        m_loadListener->updateWorldLoad();
        m_loadListener = 0;
    }

    void World::preRender(float timestep)
    {
        if(m_inputManager)
            m_inputManager->frame();
        m_tmb->frame();
        m_lastDelta = timestep;
        if(m_runService && m_runService->getRunning() && !m_runService->getPaused())
            m_ngine->updateTreeRender();
        update();
    }

    void World::preStep()
    {

    }

    double World::step(float timestep)
    {
        if(m_runService && m_runService->getRunning() && !m_runService->getPaused())
        {
            m_runService->step(timestep);
            dynamicWorldLock.lock();
            m_dynamicsWorld->stepSimulation(std::max(timestep, 0.000001f), 1);
            dynamicWorldLock.unlock();
            m_ngine->updateTree();
        }
        return 0.0;
    }

    void World::update()
    {
        m_workspace->buildGeom();
    }

}