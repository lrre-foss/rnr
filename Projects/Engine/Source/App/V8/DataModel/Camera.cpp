#include <App/V8/DataModel/Camera.hpp>
#include <Helpers/XML.hpp>

namespace RNR
{
    Camera::Camera()
    {
        //
    }

    Camera::~Camera()
    {
        //
    }

    void Camera::deserializeProperty(char* prop_name, pugi::xml_node node)
    {
        if(prop_name == std::string("CoordinateFrame"))
        {
            setCFrame(XML::getCFrame(node));
        }
    }

    void Camera::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("CFrame"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_CFRAME,         
              REFLECTION_GETTER(Camera* instance = (Camera*)object; return &instance->m_cframe; ), 
              REFLECTION_SETTER(Camera* instance = (Camera*)object; instance->setCFrame(*(CoordinateFrame*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}