#include <App/V8/DataModel/Lighting.hpp>
#include <Helpers/XML.hpp>

namespace RNR
{
    Lighting::Lighting()
    {
        setName("Lighting");
        setClearColor(Ogre::Vector3(255.f/255.f,255.f/255.f,255.f/255.f));
        setShadowColor(Ogre::Vector3(127.f/255.f,127.f/255.f,127.f/255.f));
        setBottomAmbient(Ogre::Vector3(122.f/255.f,134.f/255.f,120.f/255.f));
        setTopAmbient(Ogre::Vector3(209.f/255.f,208.f/255.f,217.f/255.f));
        setSpotLight(Ogre::Vector3(191.f/255.f,191.f/255.f,191.f/255.f));
    }

    void Lighting::deserializeProperty(char* prop_name, pugi::xml_node node)
    {
        if(prop_name == std::string("ClearColor"))
        {
            setClearColor(XML::getColor(node));
        }
        else if(prop_name == std::string("ShadowColor"))
        {
            setShadowColor(XML::getColor(node));
        }
        else if(prop_name == std::string("SpotLightV9"))
        {
            setSpotLight(XML::getColor(node));
        }
        else if(prop_name == std::string("BottomAmbientV9"))
        {
            setBottomAmbient(XML::getColor(node));
        }
        else if(prop_name == std::string("TopAmbientV9"))
        {
            setTopAmbient(XML::getColor(node));
        }
    }

    void Lighting::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("BottomAmbientV9"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(Lighting* instance = (Lighting*)object; return &instance->m_bottomAmbient; ), 
              REFLECTION_SETTER(Lighting* instance = (Lighting*)object; instance->setBottomAmbient(*(Ogre::Vector3*)value); ) },
            { this, std::string("TopAmbientV9"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(Lighting* instance = (Lighting*)object; return &instance->m_topAmbient; ), 
              REFLECTION_SETTER(Lighting* instance = (Lighting*)object; instance->setTopAmbient(*(Ogre::Vector3*)value); ) },
            { this, std::string("ClearColor"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(Lighting* instance = (Lighting*)object; return &instance->m_clearColor; ), 
              REFLECTION_SETTER(Lighting* instance = (Lighting*)object; instance->setClearColor(*(Ogre::Vector3*)value); ) },
            { this, std::string("ShadowColor"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(Lighting* instance = (Lighting*)object; return &instance->m_shadowColor; ), 
              REFLECTION_SETTER(Lighting* instance = (Lighting*)object; instance->setShadowColor(*(Ogre::Vector3*)value); ) },
            { this, std::string("SpotLightV9"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_VECTOR3,         
              REFLECTION_GETTER(Lighting* instance = (Lighting*)object; return &instance->m_spotLight; ), 
              REFLECTION_SETTER(Lighting* instance = (Lighting*)object; instance->setSpotLight(*(Ogre::Vector3*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}