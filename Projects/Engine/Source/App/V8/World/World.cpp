#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    World::World()
    {
        m_datamodel = new Instance();
        m_datamodel->setName("DataModel");
        m_workspace = new Workspace();
        m_workspace->setParent(m_datamodel);

        Instance* test = new Instance();
        BasePart* test2 = new BasePart();
        test->setParent(m_datamodel);
        test2->setParent(m_workspace);
    }

    World::~World()
    {
        //
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
        //
    }
}