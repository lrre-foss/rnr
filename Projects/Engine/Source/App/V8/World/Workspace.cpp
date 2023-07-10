#include <App/V8/World/Workspace.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Workspace::Workspace() : Instance(), Ogre::MovableObject()
    {
        setName("Workspace");
        m_type = Ogre::String("Entity");
        m_bbox = Ogre::AxisAlignedBox(-1000,-1000,-1000, 1000,1000,1000);
    }

    void Workspace::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
        std::vector<Instance*>* children = getChildren();
        for(auto& child : *children)
        {
            renderQueueAddInstance(queue, child);
        }
    }

    void Workspace::renderQueueAddInstance(Ogre::RenderQueue* queue, Instance* instance)
    {
        std::vector<Instance*>* children = instance->getChildren();
        BasePart* rend = dynamic_cast<BasePart*>(instance);        
        queue->addRenderable(rend);

        for(auto& child : *children)
        {
            renderQueueAddInstance(queue, child);
        } 
    }

    const Ogre::String& Workspace::getMovableType(void) const
    {
        printf("Workspace::getMovableType\n");
        return m_type;
    }

    const Ogre::AxisAlignedBox& Workspace::getBoundingBox(void) const
    {
        return m_bbox;
    }

    Ogre::Real Workspace::getBoundingRadius(void) const
    {
        return 100;
    }

    void Workspace::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
    {

    }
}