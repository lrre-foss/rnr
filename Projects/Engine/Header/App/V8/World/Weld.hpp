#pragma once
#include <App/V8/Tree/Instance.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/World/ComPlicitNgine.hpp>

namespace RNR
{
    class Weld : public Instance
    {
        btRigidBody* m_aBody;
        PartInstance* m_aInstance;

        btRigidBody* m_bBody;
        PartInstance* m_bInstance;
        
        btFixedConstraint* m_constraint;
    public:
        Weld();
        ~Weld();
        virtual std::string getClassName() { return "Weld"; }

        void weld(PartInstance* a, PartInstance* b);
        void create();
        void destroy();

        bool getBroken();
    };
}