#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/CoordinateFrame.hpp>
#include <OGRE/Ogre.h>

namespace RNR
{
    class World;

    class Camera : public Instance
    {
        private:
            CoordinateFrame m_cframe;
            virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
        public:
            Camera();
            ~Camera();

            CoordinateFrame& getCFrame() { return m_cframe; };
            void setCFrame(CoordinateFrame cframe) { m_cframe = cframe; };
            bool zoom(float distance);
    };
}