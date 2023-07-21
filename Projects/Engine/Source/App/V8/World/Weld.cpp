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

    void Weld::create()
    {
        if(!m_aBody || !m_bBody)
        {
            printf("Weld::create: invalid body\n");
            return;
        }
        
		btTransform frameInA, frameInB;
		frameInA = btTransform::getIdentity();
		frameInB = btTransform::getIdentity();

        m_constraint = new btFixedConstraint(*m_aBody, *m_bBody, frameInA, frameInB);
        printf("Weld::create: welded\n");
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