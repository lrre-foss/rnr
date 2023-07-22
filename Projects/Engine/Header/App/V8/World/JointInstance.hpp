#pragma once
#include <App/V8/Tree/Instance.hpp>
#include <App/V8/DataModel/PartInstance.hpp>
#include <App/V8/World/ComPlicitNgine.hpp>

namespace RNR
{
    class JointInstance : public Instance
    {
        PartInstance *m_aInstance, *m_bInstance;
        btRigidBody *m_aBody, *m_bBody;
        CoordinateFrame m_c0, m_c1;
        virtual void addProperties(std::vector<ReflectionProperty>& properties);
        virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
    public:
        JointInstance();

        void setBodies(PartInstance* a, PartInstance* b);
        
        PartInstance* getABody() { return m_aInstance; }
        void setABody(PartInstance* a) { m_aInstance = a; }
        PartInstance* getBBody() { return m_bInstance; }
        void setBBody(PartInstance* b) { m_bInstance = b; }

        CoordinateFrame& getC0() { return m_c0; }
        void setC0(CoordinateFrame c) { m_c0 = c; }
        CoordinateFrame& getC1() { return m_c1; }
        void setC1(CoordinateFrame c) { m_c1 = c; }


        void link();
    };
}