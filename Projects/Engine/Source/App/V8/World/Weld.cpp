#include <App/V8/World/Weld.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    Weld::Weld() : JointInstance()
    {
        setName("Weld");
    }

    Weld::~Weld()
    {
        destroy();
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
}