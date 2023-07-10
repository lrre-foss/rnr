#include <App/V8/World/World.hpp>

namespace RNR
{
    World::World()
    {
        m_datamodel = new Instance();
        m_datamodel->setName("DataModel");

        Instance* test = new Instance();
        Instance* test2 = new Instance();
        test->setParent(m_datamodel);
        test2->setParent(test);
        test = new Instance();
        test->setParent(m_datamodel);
        test = new Instance();
        test->setParent(m_datamodel);
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