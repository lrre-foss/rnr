#include <App/V8/World/JointsService.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/World/ComPlicitNgine.hpp>
#include <Helpers/Bullet.hpp>

namespace RNR
{
    JointsService::JointsService()
    {
        setName("JointsService");
        m_jointsToDo = 0;
        m_jointsDone = 0;
    }

    Snap* JointsService::snap(PartInstance* a, PartInstance* b, Ogre::Vector3 contact)
    {
        //if(isWelded(a, b))
        //    return NULL;
        Snap* snap = new Snap();
        snap->setBodies(a, b);
        CoordinateFrame contactFrame;
        contactFrame.setPosition(contact);
        snap->setC0(a->getCFrame().inverse() * contactFrame);
        snap->setC1(b->getCFrame().inverse() * contactFrame);
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
            PartInstance* part0 = (PartInstance*)obj0->getUserPointer(); // A
            PartInstance* part1 = (PartInstance*)obj1->getUserPointer(); // B

            if(!w->isAncestorOf(part0) && !w->isAncestorOf(part1))
                continue;
            if(isWelded(part0, part1))
                continue;

            if(part0 && part1)
            {
                for(int j = 0; j < contact->getNumContacts(); j++)
                {
                    btManifoldPoint& pt = contact->getContactPoint(j);
                    btVector3 ptA = pt.getPositionWorldOnA();
                    btVector3 ptB = pt.getPositionWorldOnB();
                    btVector3 ptN = pt.m_normalWorldOnB;
                    
                    NormalId bFace = NORM_UNDEFINED;
                    if(ptN == btVector3(1, 0, 0))
                        bFace = NORM_RIGHT;
                    else if(ptN == btVector3(-1, 0, 0))
                        bFace = NORM_LEFT;
                    else if(ptN == btVector3(0, 1, 0))
                        bFace = NORM_UP;
                    else if(ptN == btVector3(0, -1, 0))
                        bFace = NORM_DOWN;
                    else if(ptN == btVector3(0, 0, 1))
                        bFace = NORM_FRONT;
                    else if(ptN == btVector3(0, 0, -1))
                        bFace = NORM_BACK;

                    if(bFace != NORM_UNDEFINED)
                    {
                        NormalId oFace = normalIdOpposite(bFace);
                        PartSurfaceInfo surfB = part1->getSurface(bFace);
                        PartSurfaceInfo surfA = part0->getSurface(oFace);
                        bool link = surfB.links(surfA);
                        if(link)
                        {
                            switch(part0->getSurface(bFace).type)
                            {
                            case SURFACE_WELD:
                            case SURFACE_UNIVERSAL:
                            case SURFACE_INLET:
                            case SURFACE_STUDS:
                                snap(part0,part1,Bullet::v3ToOgre(pt.m_positionWorldOnA));
                                break;
                            case SURFACE_SMOOTH:
                            default:
                                break;
                            }
                        }
                    }
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