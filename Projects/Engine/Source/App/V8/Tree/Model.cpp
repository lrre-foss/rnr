#include <App/V8/Tree/Model.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Model::Model() : PVInstance()
    {

    }

    void Model::build()
    {
        m_boundingbox.setNull();
        for(auto& child : *getChildren())
            childAddBoundingBox(child);
    }

    void Model::childAddBoundingBox(Instance* child)
    {
        for(auto& child2 : *child->getChildren())
            childAddBoundingBox(child2);
        BasePart* child_pv = (BasePart*)child;
        Ogre::Vector3 half_size = child_pv->getSize() / 2.0;
        m_boundingbox.merge(child_pv->getPosition() + half_size);
        m_boundingbox.merge(child_pv->getPosition() - half_size);
    }
}