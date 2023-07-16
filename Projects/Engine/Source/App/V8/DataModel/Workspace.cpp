#include <App/V8/DataModel/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Camera.hpp>

namespace RNR
{
    Workspace::Workspace() : ModelInstance()
    {
        setName("Workspace");
        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();    
        m_geom = world->getOgreSceneManager()->createStaticGeometry("workspaceGeom");
        m_partEntity = world->getOgreSceneManager()->createEntity("fonts/Cube.mesh");
    }

    void Workspace::onChildAdded(Instance* childAdded)
    {
        m_geomDirty = true;
    }

    void Workspace::buildGeomInstance(Instance* instance)
    {
        PartInstance* child_part = dynamic_cast<PartInstance*>(instance);
        if(child_part)
            m_geom->addEntity(m_partEntity, 
                                    child_part->getCFrame().getPosition(), 
                                    Ogre::Quaternion(child_part->getCFrame().getRotation()), 
                                    child_part->getSize());
        for(auto& child : *instance->getChildren())
            buildGeomInstance(child);
    }

    void Workspace::buildGeom()
    {
        if(!m_geomDirty)
            return;
        m_geom->reset();
        for(auto& child : *getChildren())
            buildGeomInstance(child);
        m_geom->build();
        m_geomDirty = false;
    }

    void Workspace::onChildRemoved(Instance* childRemoved)
    {
        m_geomDirty = true;
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