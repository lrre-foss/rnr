#include <App/V8/DataModel/Camera.hpp>
#include <Helpers/XML.hpp>

namespace RNR
{
    Camera::Camera()
    {
        m_cf_yaw = 0.f;
        m_cf_pitch = 0.f;
        setName("Camera");
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
        else if(prop_name == std::string("Focus"))
        {
            setFocus(XML::getCFrame(node));
        }
    }

    void Camera::cameraFrame(float xd, float yd)
    {
        Ogre::Radian pitch = Ogre::Radian(yd);
        Ogre::Radian yaw = Ogre::Radian(xd);

        Ogre::Radian old_pitch;
        Ogre::Radian old_yaw;
        Ogre::Radian old_roll;

        getCFrame().getRotation().ToEulerAnglesYXZ(old_yaw, old_pitch, old_roll);

        pitch = old_pitch + pitch;
        yaw = old_yaw - yaw;

        Ogre::Matrix3 rotation;
        rotation.FromEulerAnglesYXZ(yaw, pitch, Ogre::Radian(0));
        getCFrame().setRotation(rotation);  
    }

    void Camera::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("CFrame"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_CFRAME,         
              REFLECTION_GETTER(Camera* instance = (Camera*)object; return &instance->m_cframe; ), 
              REFLECTION_SETTER(Camera* instance = (Camera*)object; instance->setCFrame(*(CoordinateFrame*)value); ) },
            { this, std::string("Focus"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_CFRAME,         
              REFLECTION_GETTER(Camera* instance = (Camera*)object; return &instance->m_focus; ), 
              REFLECTION_SETTER(Camera* instance = (Camera*)object; instance->setFocus(*(CoordinateFrame*)value); ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }
}