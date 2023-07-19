#include <App/V8/DataModel/Workspace.hpp>
#include <App/V8/World/World.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/DataModel/Camera.hpp>

namespace RNR
{
    Workspace::Workspace() : ModelInstance()
    {
        setName("Workspace");
        m_batchMode = BATCH_STATIC_GEOMETRY;

        m_worldspawn = world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode();    
        
        switch(m_batchMode)
        {
            case BATCH_INSTANCED:
                m_instanceManager = world->getOgreSceneManager()->createInstanceManager("workspaceInstanceManager", "fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::InstanceManager::InstancingTechnique::HWInstancingBasic, 255);
                break;
            case BATCH_STATIC_GEOMETRY:
                m_geom = world->getOgreSceneManager()->createStaticGeometry("workspaceGeom");
                m_geom->setRegionDimensions(Ogre::Vector3(512,512,512));
                m_geom->setCastShadows(true);
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
                        Ogre::Entity* childEntity = (Ogre::Entity*)childAdded->getObject();
                        Ogre::InstancedEntity* replica = m_instanceManager->createInstancedEntity(childEntity->getSubEntity(0)->getMaterialName());
                        replica->setPosition(part->getPosition());
                        replica->setOrientation(part->getCFrame().getRotation());
                        replica->setScale(part->getSize());
                        childAdded->setObject(replica);
                    }
                    break;
                case BATCH_STATIC_GEOMETRY:
                    m_geom->addEntity((Ogre::Entity*)childAdded->getObject(), 
                        part->getPosition(), 
                        part->getCFrame().getRotation(),
                        part->getSize());
                    break;
            }
            child_node->setVisible(false);
            m_geomDirty = true;
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