#include <App/V8/World/JointsService.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/World/ComPlicitNgine.hpp>

namespace RNR
{
    JointsService::JointsService()
    {
        setName("JointsService");
        m_jointsToDo = 0;
        m_jointsDone = 0;
    }

    Snap* JointsService::snap(PartInstance* a, PartInstance* b)
    {
        //if(isWelded(a, b))
        //    return NULL;
        Snap* snap = new Snap();
        snap->setBodies(a, b);
        snap->setC0(b->getCFrame().toObjectSpace(a->getCFrame()));
        snap->setParent(this);
        return snap;
    }

    void JointsService::fixWelds()
    {
        for(auto& child : *getChildren())
        {
            JointInstance* weld = dynamic_cast<JointInstance*>(child);
            if(weld->getDirty())
                weld->link();
        }
    }

    void JointsService::makeJoints(Instance* w)
    {
        btDynamicsWorld* dynamicsWorld = world->getDynamicsWorld();
        dynamicsWorld->performDiscreteCollisionDetection();
        m_jointsToDo = dynamicsWorld->getDispatcher()->getNumManifolds();
        m_jointsDone = 0;
        for(int i = 0; i < m_jointsToDo; i++)
        {
            world->setLoadProgress(m_jointsDone);
            world->setMaxLoadProgress(m_jointsToDo);
            if(world->getLoadListener())
                world->getLoadListener()->updateWorldLoad();
            m_jointsDone++;

            btPersistentManifold* contact = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
            const btCollisionObject* obj0 = contact->getBody0();
            const btCollisionObject* obj1 = contact->getBody1();
            PartInstance* part0 = (PartInstance*)obj0->getUserPointer();
            PartInstance* part1 = (PartInstance*)obj1->getUserPointer();

            if(!w->isAncestorOf(part0) && !w->isAncestorOf(part1))
                continue;

            if(part0 && part1)
            {
                for(int j = 0; j < contact->getNumContacts(); j++)
                {
                    btManifoldPoint& pt = contact->getContactPoint(j);
                    btVector3 ptA = pt.getPositionWorldOnA();
                    btVector3 ptB = pt.getPositionWorldOnB();
                    btVector3 ptN = pt.m_normalWorldOnB;
                    snap(part0, part1);
                }
            }
        }
    }

    void JointsService::breakJoints(Instance* p)
    {
        for(auto& child : *getChildren())
        {
            JointInstance* snap = dynamic_cast<JointInstance*>(child);
            if(snap)
            {
                bool brk = false;
                if(snap->getABody() == p)
                    brk = true;
                else if(snap->getBBody() == p)
                    brk = true;
                if(brk)
                {
                    snap->setParent(NULL);
                    delete snap;
                }
            }
        }
    }

    bool JointsService::isWelded(PartInstance* a, PartInstance* b)
    {
        for(auto& child : *getChildren())
        {
            JointInstance* snap = dynamic_cast<JointInstance*>(child);
            if(snap)
            {
                if(snap->getABody() == a && snap->getBBody() == b)
                    return true;
                else if(snap->getABody() == b && snap->getBBody() == a)
                    return true;
            }
        }
        return false;
    }
}