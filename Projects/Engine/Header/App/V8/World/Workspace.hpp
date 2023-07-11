#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <OGRE/Ogre.h>

namespace RNR
{
    class Workspace : public Instance
    {
    public:
        Workspace();

        void build();
    private:
        Ogre::InstanceManager* m_instMan;
        Ogre::SceneNode* m_worldspawn;

        void buildChild(Instance* child);        
    };
}
