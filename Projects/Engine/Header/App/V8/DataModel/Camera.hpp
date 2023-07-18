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
        virtual void addProperties(std::vector<ReflectionProperty>& properties);
        public:
            Camera();
            ~Camera();

            virtual std::string getClassName() { return "Camera"; }
            CoordinateFrame& getCFrame() { return m_cframe; };
            void setCFrame(CoordinateFrame cframe) { m_cframe = cframe; };
            bool zoom(float distance);
    };
}