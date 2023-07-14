#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/V8/DataModel/Workspace.hpp>
#include <OGRE/Ogre.h>

namespace RNR
{
    class World
    {
        private:
            Instance* m_datamodel;
            Workspace* m_workspace;
            Ogre::Root* m_ogreRoot;
            Ogre::SceneManager* m_ogreSceneManager;

        public:
            World(Ogre::Root* ogre, Ogre::SceneManager* ogreScene);
            ~World();

            void preStep();
            double step(float timestep);
            void update();

            Instance* getDatamodel() { return m_datamodel; }
            void setDatamodel(Instance* instance) { m_datamodel = instance; }
            Workspace* getWorkspace() { return m_workspace; }
            void setWorkspace(Workspace* workspace) { m_workspace = workspace; }
            Ogre::Root* getOgreRoot() { return m_ogreRoot; }
            Ogre::SceneManager* getOgreSceneManager() { return m_ogreSceneManager; }
    };
}