#include <App/V8/DataModel/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Camera.hpp>

namespace RNR
{
    Workspace::Workspace() : ModelInstance()
    {
        m_instancingEnabled = false;
        setName("Workspace");
        m_instMan = world->getOgreSceneManager()->createInstanceManager("workspacePartInstanceManager", "fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 255);
        m_instMan->setNumCustomParams(2);        
        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();    
        m_legacyGeom = world->getOgreSceneManager()->createStaticGeometry("workspaceGeom");
        m_partEntity = world->getOgreSceneManager()->createEntity("fonts/Cube.mesh");
    }

    void Workspace::onChildAdded(Instance* childAdded)
    {
        PartInstance* child_part = dynamic_cast<PartInstance*>(childAdded);
        if(child_part)
        {
            if(m_instancingEnabled)
            {
                Ogre::InstancedEntity* child_ent = (Ogre::InstancedEntity*)childAdded->getObject();
                if(!child_ent)
                {
                    child_ent = m_instMan->createInstancedEntity("materials/partinstanced");        
                    assert(child_ent != NULL);
                    childAdded->setObject(child_ent);
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
            else
            {
                m_legacyGeom->addEntity(m_partEntity, 
                                        child_part->getCFrame().getPosition(), 
                                        Ogre::Quaternion(child_part->getCFrame().getRotation()), 
                                        child_part->getSize());
                m_legacyDirty = true;
            }
        }
    }

    void Workspace::buildLegacyGeom()
    {
        m_legacyGeom->build();
        m_legacyDirty = false;
    }

    void Workspace::onChildRemoved(Instance* childRemoved)
    {
        Ogre::InstancedEntity* child_ent = (Ogre::InstancedEntity*)childRemoved->getObject();
        if(child_ent)
        {
            PartInstance* child_part = dynamic_cast<PartInstance*>(childRemoved);
            if(child_part)
            {
                child_ent->_getOwner()->removeInstancedEntity(child_ent);
                child_part->setObject(NULL);            

                auto child_it = std::find(m_objects.begin(), m_objects.end(), child_ent);
                if (child_it != m_objects.end())
                {
                    m_objects.erase(child_it);
                }
            }

            delete child_ent;
        }
    }

    Camera* Workspace::getCurrentCamera() const
    {
        return currentCamera.get();
    }

    void Workspace::setCurrentCamera(Camera *newCamera)
    {
        if (newCamera != currentCamera.get())
        {
            currentCamera = std::shared_ptr<Camera>(newCamera);

            // TODO: raise propertyChanged and currentCameraChangedSignal
        }
    }
}