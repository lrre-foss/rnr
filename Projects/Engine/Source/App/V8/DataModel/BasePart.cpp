#include <App/V8/DataModel/BasePart.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    Ogre::MeshPtr BasePart::m_partMesh = 0;

    BasePart::BasePart() : m_matrix(), PVInstance(), Ogre::Renderable()
    {
        setName("Part");

        updateMatrix();
        m_nearbyLights = Ogre::LightList();
        m_nearbyLights.insert(m_nearbyLights.begin(), world->getOgreSceneManager()->getLight("SunLight"));

        m_material = Ogre::MaterialManager::getSingletonPtr()->create("part", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        if(m_partMesh == 0)
            m_partMesh = Ogre::Root::getSingletonPtr()->getMeshManager()->load("fonts/Cube.mesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    }

    void BasePart::updateMatrix()
    {
        m_matrix = m_cframe.getMatrix();
        m_position = m_cframe.getPosition();
    }

    const Ogre::MaterialPtr& BasePart::getMaterial() const
    {
        Ogre::SubMesh* submesh = m_partMesh->getSubMesh(0);
        return submesh->getMaterial();
    }

    void BasePart::getRenderOperation(Ogre::RenderOperation& op)
    {
        Ogre::SubMesh* submesh = m_partMesh->getSubMesh(0);
        if(submesh)
        {
            op.operationType = op.OT_TRIANGLE_LIST;
            if(submesh->useSharedVertices == false)
                op.vertexData = submesh->vertexData;
            else
                op.vertexData = m_partMesh->sharedVertexData;
            op.indexData = submesh->indexData;
            op.numberOfInstances = 1;
            op.srcRenderable = this;
            op.useIndexes = true;
        }
        else
            printf("BasePart::getRenderOperation: couldnt get submesh\n");
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
        *xform = m_matrix;
    }
}