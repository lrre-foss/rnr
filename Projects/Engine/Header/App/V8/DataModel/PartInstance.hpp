#pragma once
#include <App/V8/Tree/PVInstance.hpp>
#include <App/BrickColor.hpp>
#include <OGRE/Ogre.h>

#define STUD_HEIGHT 1.18

namespace RNR
{
    class PartInstance : public PVInstance
    {
    protected:
        int m_brickColor;
        Ogre::Matrix4 m_matrix;
        Ogre::Vector3 m_position;
        Ogre::Vector3 m_size;
        Ogre::Vector4 m_color;
        virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
        virtual void addProperties(std::vector<ReflectionProperty>& properties);
        std::string mesh_id;
    public:
        PartInstance();

        void updateMatrix();

        virtual std::string getClassName() { return "PartInstance"; }
        void setSize(Ogre::Vector3 size) { m_size = size; }
        Ogre::Vector3 getSize() { return m_size; }
        Ogre::Vector4 getColor() { return m_color; }

        void setBrickColor(int brickcolor) { m_brickColor = brickcolor; }
        int getBrickColor() { return m_brickColor; }
    };
}