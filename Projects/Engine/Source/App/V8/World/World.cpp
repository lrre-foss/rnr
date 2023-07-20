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
#include <Helpers/Bullet.hpp>

namespace RNR
{
    void physicsThread(World* world)
    {
        float delta;
        float time;
        while(world->getPhysicsShouldBeRunningPleaseStopIfItIsStillRunning())
        {
            delta = world->getPhysicsTimer()->getMicroseconds() / 1000000.0;
            time += world->getPhysicsTimer()->getMilliseconds() / 1000.0;
            world->setPhysicsTime(time);
            world->getPhysicsTimer()->reset();
            world->preStep();
            world->step(delta);
        }
    }

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

        m_runPhysics = true;
        m_physicsTimer = new Ogre::Timer();
        m_physicsThread = std::thread(physicsThread, this);

        m_tmb = new TopMenuBar(this);

        Camera* start_cam = new Camera();
        start_cam->setParent(m_workspace);
        m_workspace->setCurrentCamera(start_cam);
    }

    World::~World()
    {
        m_runPhysics = false;
        m_physicsThread.join();
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
        }
        m_workspace->build();
    }

    void World::preRender(float timestep)
    {
        if(m_inputManager)
            m_inputManager->frame();
        m_tmb->frame();
        m_lastDelta = timestep;
        physicsIterateLock.lock();
        for(int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
            if(!obj->isActive())
                continue;
            PartInstance* part = (PartInstance*)obj->getUserPointer();
            part->updateMatrix();
        }
        physicsIterateLock.unlock();
    }

    void World::preStep()
    {

    }

    double World::step(float timestep)
    {
        if(m_runService && m_runService->getRunning() && !m_runService->getPaused())
        {
            m_runService->step(timestep);
            m_dynamicsWorld->stepSimulation(timestep, 2);

            physicsIterateLock.lock();
            for(int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
            {
                btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
                if(!obj->isActive())
                    continue;
                btRigidBody* body = btRigidBody::upcast(obj);
                btTransform trans;
                if(body && body->getMotionState())
                {
                    body->getMotionState()->getWorldTransform(trans);
                }
                else
                {
                    trans = obj->getWorldTransform();
                }
                PartInstance* part = (PartInstance*)obj->getUserPointer();
                part->getCFrame().setPosition(Bullet::v3ToOgre(trans.getOrigin()));
                Ogre::Matrix3 partRot;
                Ogre::Quaternion transOgre = Bullet::qtToOgre(trans.getRotation());
                transOgre.ToRotationMatrix(partRot);
                part->getCFrame().setRotation(partRot);
            }
            physicsIterateLock.unlock();
        }
        m_lastPhysicsDelta = timestep;
        return 0.0;
    }

    void World::update()
    {
        m_workspace->buildGeom();
    }

    void World::registerPhysicsPart(PartInstance* partRegistered)
    {
        btCollisionShape* partShape = new btBoxShape(Bullet::v3ToBullet(partRegistered->getSize() / 2.f));
        partShape->setUserPointer(partRegistered);

        btTransform partTransform;
        partTransform.setIdentity();
        partTransform.setOrigin(Bullet::v3ToBullet(partRegistered->getPosition()));
        partTransform.setRotation(Bullet::qtToBullet(partRegistered->getRotation()));
        
        btScalar mass = partRegistered->getSize().length();
        if(partRegistered->getAnchored())
            mass = 0;
        
        btVector3 localInertia = btVector3(0,0,0);        
        if(mass)
            partShape->calculateLocalInertia(mass, localInertia);
            
        btDefaultMotionState* partMotionState = new btDefaultMotionState(partTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, partMotionState, partShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);
        body->setUserPointer(partRegistered);

        m_dynamicsWorld->addRigidBody(body);
    }

    void World::deletePhysicsPart(PartInstance* partDelete)
    {

    }
}