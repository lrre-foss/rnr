#pragma once
#include <App/V8/Tree/PVInstance.hpp>

namespace RNR
{
    class ModelInstance : public PVInstance
    {
    public:
        ModelInstance();

        virtual void build();
        Ogre::AxisAlignedBox getBoundingBox() { return m_boundingbox; }
        virtual std::string getClassName() { return "Model"; }
    private:
        Ogre::AxisAlignedBox m_boundingbox;
        
        void childAddBoundingBox(Instance* child);
    };
}