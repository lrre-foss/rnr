#include <App/V8/DataModel/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Camera.hpp>

namespace RNR
{
    Workspace::Workspace() : ModelInstance()
    {
        setName("Workspace");
        m_batchMode = BATCH_INSTANCED;

        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();    

        switch(m_batchMode)
        {
            case BATCH_INSTANCED:
                m_instanceManager = world->getOgreSceneManager()->createInstanceManager("workspaceInstanceManager", "meshes/Cube_Instanced.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 255);
                break;
            case BATCH_STATIC_GEOMETRY:
                m_geom = world->getOgreSceneManager()->createStaticGeometry("workspaceGeom");
                m_geom->setRegionDimensions(Ogre::Vector3(4096, 4096, 4096));
                m_geom->setCastShadows(true);
                break;
            case BATCH_DONT:
                break;
        }
    }

    void Workspace::onDescendantAdded(Instance* childAdded)
    {
        PartInstance* part = dynamic_cast<PartInstance*>(childAdded);
        if(part)
        {
            Ogre::SceneNode* child_node = childAdded->getNode();
            switch(m_batchMode)
            {
                case BATCH_INSTANCED:
                    {
                        Ogre::InstancedEntity* replica = m_instanceManager->createInstancedEntity(BrickColor::material(part->getBrickColor())->getName());
                        part->updateMatrix();
                        replica->setPosition(part->getCFrame().getPosition());
                        replica->setOrientation(part->getCFrame().getRotation());
                        replica->setScale(part->getSize());
                        replica->setCastShadows(true);
                        m_worldspawn->attachObject(replica);
                        childAdded->setObject(replica);
                        child_node->setVisible(false);
                    }
                    break;
                case BATCH_STATIC_GEOMETRY:
                    m_geom->addEntity((Ogre::Entity*)childAdded->getObject(), 
                        part->getPosition(), 
                        part->getCFrame().getRotation(),
                        part->getSize());
                    child_node->setVisible(false);
                    m_geomDirty = true;
                    break;
                case BATCH_DONT:
                    child_node->setVisible(true);
                    break;
            }
            world->getComPlicitNgine()->registerPhysicsPart(part);
        }
    }

    void Workspace::buildGeomInstance(Instance* instance)
    {

    }

    void Workspace::buildGeom()
    {
        if(!m_geomDirty || m_batchMode != BATCH_STATIC_GEOMETRY)
            return;
        m_geom->build();
        m_geomDirty = false;
    }

    void Workspace::onDescendantRemoved(Instance* childRemoved)
    {
        PartInstance* part = dynamic_cast<PartInstance*>(childRemoved);
        if(part)
            world->getComPlicitNgine()->deletePhysicsPart(part);
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

    void Workspace::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("CurrentCamera"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(Workspace* instance = (Workspace*)object; return instance->currentCamera.get(); ), 
              REFLECTION_SETTER(Workspace* instance = (Workspace*)object; instance->setCurrentCamera((Camera*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}