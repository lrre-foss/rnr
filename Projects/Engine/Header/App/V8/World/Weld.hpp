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

        virtual void addProperties(std::vector<ReflectionProperty>& properties);
        virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
    public:
        Weld();
        ~Weld();
        virtual std::string getClassName() { return "Weld"; }

        void weld(PartInstance* a, PartInstance* b);
        bool create();
        void destroy();

        bool getBroken();
        PartInstance* getPartA() { return m_aInstance; }
        PartInstance* getPartB() { return m_bInstance; }
    };

    class Snap : public Weld
    {
        // they're basically the same
    public:
        virtual std::string getClassName() { return "Snap"; }
        virtual std::string getExplorerIcon() { return "Weld"; }
    };
}