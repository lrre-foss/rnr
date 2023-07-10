#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Ogre::MeshPtr BasePart::m_partMesh = 0;

    BasePart::BasePart() : m_matrix(), PVInstance()
    {
        setName("Part");
        
        updateMatrix();

        m_material = Ogre::MaterialManager::getSingletonPtr()->create("part", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        if(m_partMesh == 0)
            m_partMesh = Ogre::Root::getSingletonPtr()->getMeshManager()->load("fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    }

    void BasePart::updateMatrix()
    {
        m_matrix = m_cframe.getMatrix();
        m_position = m_cframe.getPosition();
        m_nearbyLights = Ogre::LightList();

    }

    const Ogre::MaterialPtr& BasePart::getMaterial() const
    {
        return m_material;
    }

    void BasePart::getRenderOperation(Ogre::RenderOperation& op)
    {
        Ogre::SubMesh* submesh = m_partMesh->getSubMesh(0);
        op.operationType = op.OT_TRIANGLE_LIST;
        op.vertexData = submesh->vertexData;
        op.indexData = submesh->indexData;
        op.numberOfInstances = 1;
        op.srcRenderable = this;
        op.useIndexes = true;
    }

    Ogre::Real BasePart::getSquaredViewDepth(const Ogre::Camera* cam) const
    {
        Ogre::Vector3 diff = m_position - cam->getDerivedPosition();
        return diff.squaredLength();
    }

    const Ogre::LightList& BasePart::getLights() const
    {
        return m_nearbyLights;
    }

    void BasePart::getWorldTransforms(Ogre::Matrix4* xform) const
    {
        xform[0] = m_matrix;
    }
}