#pragma once
#include "LinearMath/btVector3.h"
#include "btBulletDynamicsCommon.h"
#include <OGRE/Ogre.h>

namespace RNR
{
    class Bullet
    {
    public:
        static btVector3 v3ToBullet(Ogre::Vector3 v);
        static Ogre::Vector3 v3ToOgre(btVector3 v);
        static btQuaternion qtToBullet(Ogre::Quaternion q);
        static Ogre::Quaternion qtToOgre(btQuaternion q);
    };
}