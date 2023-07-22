#include <App/V8/World/ComPlicitNgine.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/World/JointsService.hpp>
#include <Helpers/Bullet.hpp>

namespace RNR
{
    void ComPlicitNgine::thread()
    {
        float delta;
        float time;
        while(m_world->getPhysicsShouldBeRunningPleaseStopIfItIsStillRunning())
        {
            delta = m_physicsTimer->getMicroseconds() / 1000000.0;
            time += m_physicsTimer->getMilliseconds() / 1000.0;
            m_physicsTimer->reset();
            
            m_lastPhysicsDelta = delta;
            m_physicsTime = time;

            if(m_lastPhysicsDelta == 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            
            if(m_world->getRunService()->getRunning())
            {
                JointsService* joints = (JointsService*)m_world->getDatamodel()->getService("JointsService");
                joints->fixWelds();
                m_world->preStep();
                m_world->step(delta);
            }


            m_lastPhysicsDelta = delta;
        }
    }

    ComPlicitNgine::ComPlicitNgine(World* world)
    {
        m_physicsTimer = new Ogre::Timer();
        m_physicsTime = 0.0;
        m_physicsThread = std::thread(&ComPlicitNgine::thread, this);
        m_dynamicsWorld = world->getDynamicsWorld();
        m_world = world;
    }

    ComPlicitNgine::~ComPlicitNgine()
    {
        m_physicsThread.join();
    }

    void ComPlicitNgine::updateTreeRender()
    {
        for(int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
            if(obj->getActivationState() != ACTIVE_TAG)
                continue;
            PartInstance* part = (PartInstance*)obj->getUserPointer();
            if(part)
            {
                part->updateMatrix();
            }
        }   
    }

    void ComPlicitNgine::updateTree()
    {
        m_activeObjects = 0;
        m_sleepingObjects = 0;
        for(int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
            if(obj->getActivationState() != ACTIVE_TAG) { m_sleepingObjects++; continue; }
            m_activeObjects++;
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
            if(part)
            {
                part->getCFrame().setPosition(Bullet::v3ToOgre(trans.getOrigin()));
                Ogre::Matrix3 partRot;
                Ogre::Quaternion transOgre = Bullet::qtToOgre(trans.getRotation());
                transOgre.ToRotationMatrix(partRot);
                part->getCFrame().setRotation(partRot);
            }
        }
    }

    void ComPlicitNgine::registerPhysicsPart(PartInstance* partRegistered)
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

        m_world->dynamicWorldLock.lock();
        m_dynamicsWorld->addRigidBody(body);        
        m_world->dynamicWorldLock.unlock();

        m_physicsParts[partRegistered] = body;
    }

    void ComPlicitNgine::updatePhysicsPart(PartInstance* partUpdate)
    {
        btRigidBody* toUpdate = m_physicsParts[partUpdate];
        if(toUpdate)
        {
            btTransform& bodytf = toUpdate->getWorldTransform();
            bodytf.setIdentity();
            bodytf.setOrigin(Bullet::v3ToBullet(partUpdate->getPosition()));
            bodytf.setRotation(Bullet::qtToBullet(partUpdate->getRotation()));
        }
    }

    void ComPlicitNgine::deletePhysicsPart(PartInstance* partDelete)
    {
        btRigidBody* toDelete = m_physicsParts[partDelete];
        if(toDelete)
        {
            
        }
    }
}