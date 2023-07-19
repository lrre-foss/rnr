#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/World/World.hpp>
#include <Helpers/XML.hpp>

namespace RNR
{
    PartInstance::PartInstance() : m_matrix(), PVInstance(),  m_size(2.f, STUD_HEIGHT, 4.f)
    {
        setName("Part");

        m_color = Ogre::Vector4(0.63, 0.64, 0.63, 1.0);
        m_transparency = 0.0;
        m_reflectance = 0.0;

        setNode(world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode());
        setObject(world->getOgreSceneManager()->createEntity("fonts/Cube.mesh"));
        getNode()->attachObject(getObject());

        updateMatrix();
    }

    void PartInstance::updateMatrix()
    {
        m_matrix = m_cframe.getMatrix(); 
        m_position = m_cframe.getPosition();

        getNode()->setOrientation(Ogre::Quaternion(m_cframe.getRotation()));
        getNode()->setPosition(m_position);
        getNode()->setScale(m_size);

        Ogre::Entity* entity = (Ogre::Entity*)getObject();
        for(auto& subentity : entity->getSubEntities())
        {
            subentity->setMaterial(BrickColor::material(m_brickColor));
            subentity->getMaterial()->setShininess(64);
        }
    }

    void PartInstance::deserializeProperty(char* prop_name, pugi::xml_node node)
    {
        if(prop_name == std::string("size"))
        {
            setSize(XML::getVector3(node));
        }
        else if(prop_name == std::string("BrickColor"))
        {
            setBrickColor(node.text().as_int());
            if(!BrickColor::valid(getBrickColor()))
            {
                printf("PartInstance::deserializeProperty: BrickColor not valid number (%i)\n", getBrickColor());
            }
        }
        else if(prop_name == std::string("Reflectance"))
        {
            setReflectance(node.text().as_float());
        }
        else if(prop_name == std::string("Transparency"))
        {
            setTransparency(node.text().as_float());
        }
        else
            PVInstance::deserializeProperty(prop_name, node);
        updateMatrix();
    }

    void PartInstance::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("Size"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(PartInstance* instance = (PartInstance*)object; return &instance->m_size; ), 
              REFLECTION_SETTER(PartInstance* instance = (PartInstance*)object; instance->setSize(*(Ogre::Vector3*)value); ) },
            { this, std::string("BrickColor"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_BRICKCOLOR,         
              REFLECTION_GETTER(PartInstance* instance = (PartInstance*)object; return &instance->m_brickColor; ), 
              REFLECTION_SETTER(PartInstance* instance = (PartInstance*)object; instance->setBrickColor(*(int*)value); ) },
            { this, std::string("Reflectance"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_FLOAT,         
              REFLECTION_GETTER(PartInstance* instance = (PartInstance*)object; return &instance->m_reflectance; ), 
              REFLECTION_SETTER(PartInstance* instance = (PartInstance*)object; instance->setReflectance(*(float*)value); ) },
            { this, std::string("Transparency"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_FLOAT,         
              REFLECTION_GETTER(PartInstance* instance = (PartInstance*)object; return &instance->m_transparency; ), 
              REFLECTION_SETTER(PartInstance* instance = (PartInstance*)object; instance->setTransparency(*(float*)value); ) },
        };

        PVInstance::addProperties(properties);
        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}