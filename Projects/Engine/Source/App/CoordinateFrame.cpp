#include <App/CoordinateFrame.hpp>

namespace RNR
{
    CoordinateFrame::CoordinateFrame() : m_position(0.f,0.f,0.f), m_scale(1.f,1.f,1.f), m_rotation()
    {
        m_rotation.FromEulerAnglesXYZ(Ogre::Radian(0.f), Ogre::Radian(0.f), Ogre::Radian(0.f));        
    }

    Ogre::Matrix4 CoordinateFrame::getMatrix()
    {
        Ogre::Matrix4 res = Ogre::Matrix4();
        res.makeTransform(m_position, m_scale, Ogre::Quaternion(m_rotation));
        return res;
    }

    CoordinateFrame CoordinateFrame::operator+(Ogre::Vector3 vector)
    {
        CoordinateFrame res;
        res.m_position = m_position + vector;
        return res;
    }

    CoordinateFrame CoordinateFrame::operator*(CoordinateFrame frame)
    {
        CoordinateFrame res;
        res.m_position = m_position * frame.m_position;
        res.m_rotation = m_rotation * frame.m_rotation;
        return res;
    }
}