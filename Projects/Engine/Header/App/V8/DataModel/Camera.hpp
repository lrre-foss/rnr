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
            CoordinateFrame m_focus;
            Ogre::Radian m_yaw;
            virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
            virtual void addProperties(std::vector<ReflectionProperty>& properties);
        public:
            Camera();
            ~Camera();

            void cameraFrame(float xd, float yd, bool movement_disable = true);

            virtual std::string getClassName() { return "Camera"; }
            CoordinateFrame& getCFrame() { return m_cframe; };
            CoordinateFrame& getFocus() { return m_focus; }
            Ogre::Radian getYaw() { return m_yaw; }
            void setCFrame(CoordinateFrame cframe) { m_cframe = cframe; };
            void setFocus(CoordinateFrame focus) { m_focus = focus; }
            bool zoom(float distance);
    };
}