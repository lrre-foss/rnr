#include <App/V8/Tree/PVInstance.hpp>
#include <Helpers/XML.hpp>

namespace RNR
{
    PVInstance::PVInstance() : m_cframe(), Instance()
    {
        
    }

    void PVInstance::deserializeProperty(char* prop_name, pugi::xml_node node)
    {
        if(prop_name == std::string("CFrame"))
        {
            setCFrame(XML::getCFrame(node));
        }
    }
}