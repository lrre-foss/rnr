#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/V8/Tree/Model.hpp>
#include <OGRE/Ogre.h>
#include <vector>

namespace RNR
{
    class Workspace : public Model
    {
    public:
        Workspace();

        virtual void build();
        void clean();
    private:
        std::vector<Ogre::InstancedEntity*> m_objects;
        Ogre::InstanceManager* m_instMan;
        Ogre::SceneNode* m_worldspawn;

        void buildChild(Instance* child);        
    };
}
