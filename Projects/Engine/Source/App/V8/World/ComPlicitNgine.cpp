#include <App/V8/World/ComPlicitNgine.hpp>
#include <App/V8/World/World.hpp>
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
            
            m_world->preStep();
            m_world->step(delta);

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
        m_world->physicsIterateLock.lock();
        for(int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
            if(!obj->isActive())
                continue;
            PartInstance* part = (PartInstance*)obj->getUserPointer();
            part->updateMatrix();
        }
        m_world->physicsIterateLock.unlock();        
    }

    void ComPlicitNgine::updateTree()
    {
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

        m_world->physicsIterateLock.lock();
        m_dynamicsWorld->addRigidBody(body);        
        m_world->physicsIterateLock.unlock();

        m_physicsParts[partRegistered] = body;
    }

    void ComPlicitNgine::deletePhysicsPart(PartInstance* partDelete)
    {
        btRigidBody* toDelete = m_physicsParts[partDelete];
        if(toDelete)
        {
            
        }
    }
}