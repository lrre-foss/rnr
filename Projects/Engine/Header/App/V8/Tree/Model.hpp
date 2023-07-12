#pragma once
#include <App/V8/Tree/PVInstance.hpp>

namespace RNR
{
    class Model : public PVInstance
    {
    public:
        Model();

        virtual void build();
        Ogre::AxisAlignedBox getBoundingBox() { return m_boundingbox; }
    private:
        Ogre::AxisAlignedBox m_boundingbox;
        
        void childAddBoundingBox(Instance* child);
    };
}