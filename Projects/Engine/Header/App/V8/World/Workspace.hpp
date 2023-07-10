#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <OGRE/Ogre.h>

namespace RNR
{
    // this acts as both an Instance to fit in the RNR graph, and as an Ogre MovableObject to fit in the Ogre graph
    // all instances that are Renderable are stored in the children of this
    class Workspace : public Instance, public Ogre::MovableObject
    {
    public:
        Workspace();

        virtual void _updateRenderQueue(Ogre::RenderQueue* queue);
        virtual const Ogre::String& getMovableType(void) const;
        virtual const Ogre::AxisAlignedBox& getBoundingBox(void) const;
        virtual Ogre::Real getBoundingRadius(void) const;
        virtual void visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables);
    private:
        void renderQueueAddInstance(Ogre::RenderQueue* queue, Instance* instance);
    };
}
