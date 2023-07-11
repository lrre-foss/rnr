#pragma once
#include <OGRE/Ogre.h>

namespace RNR
{
    class CoordinateFrame
    {
        Ogre::Vector3 m_position;
        Ogre::Vector3 m_scale;
        Ogre::Matrix3 m_rotation;
public:
        CoordinateFrame();

        Ogre::Matrix3 getRotation() { return m_rotation; }
        Ogre::Vector3 getPosition() { return m_position; }

        Ogre::Matrix4 getMatrix();

        CoordinateFrame operator+(Ogre::Vector3 vector);
        CoordinateFrame operator*(CoordinateFrame frame);
    };
}