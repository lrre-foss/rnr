#include <App/V8/World/JointInstance.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    JointInstance::JointInstance()
    {
        setName("Joint");
    }

    void JointInstance::setBodies(PartInstance* a, PartInstance* b)
    {
        m_aInstance = a;
        m_bInstance = b;

        m_aBody = world->getComPlicitNgine()->getBody(a);
        m_bBody = world->getComPlicitNgine()->getBody(b);
    }

    void JointInstance::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("Part0"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(JointInstance* instance = (JointInstance*)object; return instance->m_aInstance; ), 
              REFLECTION_SETTER(JointInstance* instance = (JointInstance*)object;  ) },
            { this, std::string("Part1"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(JointInstance* instance = (JointInstance*)object; return instance->m_bInstance; ), 
              REFLECTION_SETTER(JointInstance* instance = (JointInstance*)object;  ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }

    void JointInstance::deserializeProperty(char* prop_name, pugi::xml_node prop)
    {

    }
}