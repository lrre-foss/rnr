#include <App/V8/DataModel/Light.hpp>

namespace RNR
{
    Light::Light()
    {
        m_brightness = 1.f;
        m_enabled = true;
        m_shadows = true;
        m_color = Ogre::Vector3(1.f,1.f,1.f);        
    }
}