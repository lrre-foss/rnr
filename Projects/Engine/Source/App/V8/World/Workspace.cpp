#include <App/V8/World/Workspace.hpp>
#include <App/V8/DataModel/BasePart.hpp>

namespace RNR
{
    Workspace::Workspace() : Instance(), Ogre::MovableObject()
    {
        setName("Workspace");
    }

    void Workspace::_updateRenderQueue(Ogre::RenderQueue* queue)
    {
        printf("!!!!!!!!!!!!!!!!!!!!1 _updateRenderQueue\n");
        std::vector<Instance*>* children = getChildren();
        for(auto& child : *children)
        {
            renderQueueAddInstance(queue, child);
        }
    }

    void Workspace::renderQueueAddInstance(Ogre::RenderQueue* queue, Instance* instance)
    {
        std::vector<Instance*>* children = instance->getChildren();
        for(auto& child : *children)
        {
            renderQueueAddInstance(queue, child);
        } 
        BasePart* rend = dynamic_cast<BasePart*>(instance);        
        queue->addRenderable(rend);
    }

    const Ogre::String& Workspace::getMovableType(void) const
    {
        return Ogre::String("Entity");
    }

    const Ogre::AxisAlignedBox& Workspace::getBoundingBox(void) const
    {
        return Ogre::AxisAlignedBox(Ogre::Vector3(-1000,-1000,-1000),Ogre::Vector3(1000,1000,1000));
    }

    Ogre::Real Workspace::getBoundingRadius(void) const
    {
        return 100;
    }

    void Workspace::visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables)
    {

    }
}