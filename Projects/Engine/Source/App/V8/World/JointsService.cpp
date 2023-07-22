#include <App/V8/World/JointsService.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    JointsService::JointsService()
    {
        setName("JointsService");
    }

    Snap* JointsService::snap(PartInstance* a, PartInstance* b)
    {
        Snap* snap = new Snap();
        snap->setBodies(a, b);
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

    void JointsService::makeJoints(Instance* w, PartInstance* p)
    {
        for(auto& child : *w->getChildren())
        {
            if(child == p)
                continue;
            PartInstance* child_p = dynamic_cast<PartInstance*>(child);
            if(child_p)
            {
                if(isWelded(child_p, p))
                    continue;
                if(p == child_p)
                    continue;
                child_p->updateSurfaces();
                for(int i = 0; i < __NORM_COUNT; i++)
                {
                    NormalId n = (NormalId)i;
                    NormalId n_opp = normalIdOpposite(n);
                    PartSurfaceInfo n_surf = p->getSurface(n);
                    PartSurfaceInfo n_opp_surf = child_p->getSurface(n_opp);
                    if(n_surf.intersects(n_opp_surf))
                    {
                        if(n_surf.links(n_opp_surf))
                        {
                            // determine link
                            switch(n_surf.type)
                            {
                                case SURFACE_WELD:
                                case SURFACE_STUDS:
                                case SURFACE_INLET:
                                    snap(p, child_p);
                                    break;
                            }
                        }
                    }
                }
            }
            makeJoints(child, p);
        }
    }

    void JointsService::makeModelJoints(ModelInstance* m)
    {
        ModelInstance* parent_model = m;

        if(world->getWorkspace()->isAncestorOf(m))
        {
            parent_model = world->getWorkspace();
        }

        for(auto& child : *m->getChildren())
        {
            if(dynamic_cast<PartInstance*>(child))
                makeJoints(parent_model, (PartInstance*)child);            
        }
    }

    void JointsService::breakModelJoints(ModelInstance* m)
    {
        for(auto& child : *getChildren())
        {
            JointInstance* snap = dynamic_cast<JointInstance*>(child);
            if(snap)
            {
                bool brk = false;
                if(m->isAncestorOf(snap->getABody()))
                    brk = true;
                else if(m->isAncestorOf(snap->getBBody()))
                    brk = true;
                if(brk)
                {
                    snap->setParent(NULL);
                    delete snap;
                }
            }
        }
    }

    void JointsService::makeJoints(PartInstance* p)
    {
        p->updateSurfaces();
        makeJoints(world->getWorkspace(), p);
    }

    void JointsService::breakJoints(PartInstance* p)
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

                }
            }
        }
    }

    bool JointsService::isWelded(PartInstance* a, PartInstance* b)
    {
        for(auto& child : *getChildren())
        {
            Weld* snap = dynamic_cast<Weld*>(child);
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