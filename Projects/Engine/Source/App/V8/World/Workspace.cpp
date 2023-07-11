#include <App/V8/World/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Workspace::Workspace() : Instance()
    {
        setName("Workspace");
        m_instMan = world->getOgreSceneManager()->createInstanceManager("workspacePartInstanceManager", "fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 255);
        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    }

    void Workspace::build()
    {
        for(auto& child : *getChildren())
            buildChild(child);        
    }

    void Workspace::buildChild(Instance* child)
    {
        for(auto& child2 : *child->getChildren())
            buildChild(child2);
        BasePart* child_part = (BasePart*)child;
        Ogre::InstancedEntity* child_ent = (Ogre::InstancedEntity*)child->getObject();
        if(!child_ent)
        {
            child_ent = m_instMan->createInstancedEntity("fonts/Material");        
            child_ent->setUserAny(child);
            child->setObject(child_ent);
        }
        child_ent->setPosition(child_part->getCFrame().getPosition());
        child_ent->setOrientation(Ogre::Quaternion(child_part->getCFrame().getRotation()));

    }
}