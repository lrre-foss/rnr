#pragma once
#include <App/V8/Tree/PVInstance.hpp>
#include <OGRE/Ogre.h>

namespace RNR
{
    class BasePart : public PVInstance, public Ogre::Renderable
    {
        Ogre::MaterialPtr m_material;
        Ogre::Matrix4 m_matrix;
        Ogre::Vector3 m_position;
        Ogre::LightList m_nearbyLights;
        static Ogre::MeshPtr m_partMesh;
    public:
        BasePart();

        void updateMatrix();

        virtual const Ogre::MaterialPtr& getMaterial() const;
        virtual void getRenderOperation(Ogre::RenderOperation& op);
        virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;
        virtual const Ogre::LightList& getLights() const;
        virtual void getWorldTransforms(Ogre::Matrix4* xform) const;
    };
}