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
}