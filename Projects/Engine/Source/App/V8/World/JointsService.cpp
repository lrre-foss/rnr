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
            Weld* weld = dynamic_cast<Weld*>(child);
            weld->create();
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
                    if(n_surf.plane != n_opp_surf.plane)
                        continue;
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

    void JointsService::makeJoints(PartInstance* p)
    {
        p->updateSurfaces();
        makeJoints(world->getWorkspace(), p);
    }

    void JointsService::breakJoints(PartInstance* p)
    {
        for(auto& child : *getChildren())
        {
            Snap* snap = dynamic_cast<Snap*>(child);
            if(snap)
            {
                bool brk = false;
                if(snap->getPartA() == p)
                    brk = true;
                else if(snap->getPartB() == p)
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
                if(snap->getPartA() == a && snap->getPartB() == b)
                    return true;
                else if(snap->getPartA() == b && snap->getPartB() == a)
                    return true;
            }
        }
        return false;
    }
}