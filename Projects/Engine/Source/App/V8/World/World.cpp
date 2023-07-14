#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/BasePart.hpp>
#include <App/GUI/SelectionBox.hpp>

namespace RNR
{
    World::World(Ogre::Root* ogre, Ogre::SceneManager* ogreSceneManager)
    {
        Instance::setWorld(this);

        m_ogreRoot = ogre;
        m_ogreSceneManager = ogreSceneManager;
        m_datamodel = new Instance();
        m_datamodel->setName("DataModel");
        m_workspace = new Workspace();
        m_workspace->setParent(m_datamodel);

        Instance* test = new Instance();
        BasePart* test2 = new BasePart();
        SelectionBox* test3 = new SelectionBox();
        test->setParent(m_datamodel);
        test2->setSize(Ogre::Vector3(64,STUD_HEIGHT,64));
        test2->setName("Baseplate");
        test2->setParent(m_workspace);

        for(int i = 1; i < 36; i++)
        {
            test2 = new BasePart();
            test2->getCFrame().setPosition(Ogre::Vector3(i*2,i*STUD_HEIGHT,i*2));
            test2->setSize(Ogre::Vector3(4,STUD_HEIGHT,4));
            test2->setParent(m_workspace);
        }

        m_workspace->build();
        
        test3->setAdornee(m_workspace);
        test3->setParent(m_workspace);
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