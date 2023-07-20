#include <Helpers/Bullet.hpp>

namespace RNR
{
    btVector3 Bullet::v3ToBullet(Ogre::Vector3 v)
    {
        return btVector3(v.x, v.y, v.z);
    }

    Ogre::Vector3 Bullet::v3ToOgre(btVector3 v)
    {
        return Ogre::Vector3(v.getX(), v.getY(), v.getZ());
    }

    btQuaternion Bullet::qtToBullet(Ogre::Quaternion q)
    {
        return btQuaternion(q.x, q.y, q.z, q.w);
    }

    Ogre::Quaternion Bullet::qtToOgre(btQuaternion q)
    {
        return Ogre::Quaternion(q.getW(), q.getX(), q.getY(), q.getZ());
    }
}