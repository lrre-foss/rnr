#include <App/V8/World/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Workspace::Workspace() : Model()
    {
        setName("Workspace");
        m_instMan = world->getOgreSceneManager()->createInstanceManager("workspacePartInstanceManager", "fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 255);
        m_instMan->setNumCustomParams(2);        
        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();
    }

    void Workspace::build()
    {
        Model::build();
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
            child_ent = m_instMan->createInstancedEntity("materials/partinstanced");        
            assert(child_ent != NULL);
            child->setObject(child_ent);
            m_objects.push_back(child_ent);
        }
        child_ent->setPosition(child_part->getCFrame().getPosition());
        child_ent->setOrientation(Ogre::Quaternion(child_part->getCFrame().getRotation()));        
        Ogre::Vector3 size = child_part->getSize();
        child_ent->setScale(size);
        child_ent->setCustomParam(0, Ogre::Vector4(
            size.x,
            size.y,
            size.z,
            0.0f
        ));
        child_ent->setCustomParam(1, child_part->getColor());
        child_ent->setCastShadows(true);
    }

    void Workspace::clean()
    {

    }
}