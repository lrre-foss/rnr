#include <App/V8/World/Weld.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    Weld::Weld()
    {
        setName("Weld");
    }

    Weld::~Weld()
    {
        destroy();
    }

    void Weld::weld(PartInstance* a, PartInstance* b)
    {
        m_aInstance = a;
        m_bInstance = b;

        m_aBody = world->getComPlicitNgine()->getBody(a);
        m_bBody = world->getComPlicitNgine()->getBody(b);
    }

    bool Weld::create()
    {
        if(!m_aBody || !m_bBody)
        {
            printf("Weld::create: invalid body\n");
            return false;
        }
        
        btTransform frameInA, frameInB;
        frameInA = btTransform::getIdentity();
        frameInB = btTransform::getIdentity();

        m_constraint = new btFixedConstraint(*m_aBody, *m_bBody, frameInA, frameInB);
        printf("Weld::create: welded\n");
        return true;
    }

    void Weld::destroy()
    {
        delete m_constraint;        
    }

    bool Weld::getBroken()
    {
        if(!m_constraint)
            return true;
            
        return false;
    }

    void Weld::addProperties(std::vector<ReflectionProperty>& properties)
    {
        ReflectionProperty _properties[]  = {
            { this, std::string("Part0"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(Weld* instance = (Weld*)object; return instance->m_aInstance; ), 
              REFLECTION_SETTER(Weld* instance = (Weld*)object;  ) },
            { this, std::string("Part1"), std::string(""), 
              ACCESS_NONE, OPERATION_READWRITE, PROPERTY_INSTANCE,         
              REFLECTION_GETTER(Weld* instance = (Weld*)object; return instance->m_bInstance; ), 
              REFLECTION_SETTER(Weld* instance = (Weld*)object;  ) },
        };

        properties.insert(properties.end(), _properties, _properties+(sizeof(_properties)/sizeof(ReflectionProperty)));
    }

    void Weld::deserializeProperty(char* prop_name, pugi::xml_node prop)
    {

    }
}