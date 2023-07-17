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
        m_geom->setCastShadows(true);
        m_partEntity = world->getOgreSceneManager()->createEntity("fonts/Cube.mesh");
        m_partEntity->setCastShadows(true);

        for(int i = 0; i < m_partEntity->getNumSubEntities(); i++)
        {
            Ogre::SubEntity* surface = m_partEntity->getSubEntity(i);
            Ogre::TextureUnitState* texture = surface->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState("textures/stud_top.png");
        }
    }

    void Workspace::onChildAdded(Instance* childAdded)
    {
        m_geomDirty = true;
    }

    void Workspace::buildGeomInstance(Instance* instance)
    {
        PartInstance* child_part = dynamic_cast<PartInstance*>(instance);
        if(child_part)
        {
            Ogre::Vector3 part_size = child_part->getSize();
            for(int i = 0; i < m_partEntity->getNumSubEntities(); i++)
            {            
                Ogre::SubMesh* surface = m_partEntity->getMesh()->getSubMesh(i);
                Ogre::TextureUnitState* texture = surface->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

                Ogre::Vector2 uvs;
                std::string surf_name = std::string(surface->getMaterialName().c_str());
                if(surf_name == "TopMaterial")
                    uvs = Ogre::Vector2(part_size.x, part_size.z);
                else if(surf_name == "BottomMaterial")
                    uvs = Ogre::Vector2(-part_size.x, part_size.z);
                else if(surf_name == "LeftMaterial")
                    uvs = Ogre::Vector2(part_size.y, part_size.z);
                else if(surf_name == "RightMaterial")
                    uvs = Ogre::Vector2(-part_size.y, part_size.z);
                else if(surf_name == "BackMaterial")
                    uvs = Ogre::Vector2(part_size.x, part_size.z);
                else if(surf_name == "FrontMaterial")
                    uvs = Ogre::Vector2(-part_size.x, part_size.z);


            }
            m_geom->addEntity(m_partEntity,
                              child_part->getCFrame().getPosition(), 
                              Ogre::Quaternion(child_part->getCFrame().getRotation()), 
                              child_part->getSize());
        }
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

    void Workspace::deserializeProperty(char* prop_name, pugi::xml_node node)
    {
        if(prop_name == std::string("CurrentCamera"))
        {
            Instance* new_cam = world->getRef(node.text().as_string());
            if(new_cam)
                setCurrentCamera((Camera*)new_cam);
            else
                printf("Workspace::deserializeProperty: camera ref invalid (%s)\n", node.text().as_string());
        }
    }
}