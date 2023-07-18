#include <App/V8/Tree/Instance.hpp>
#include <App/V8/DataModel/FaceInstance.hpp>
#include <App/V8/World/World.hpp>
#include <Helpers/NormalId.hpp>
#include <Helpers/Strings.hpp>

namespace RNR
{
    FaceInstance::FaceInstance() : Ogre::ManualObject(Strings::random_hex(8))
    {
        setNode(world->getOgreSceneManager()->getRootSceneNode()->createChildSceneNode());
        getNode()->attachObject(this);
        build();
    }
}