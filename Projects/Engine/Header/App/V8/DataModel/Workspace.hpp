#pragma once

#include <App/V8/Tree/Instance.hpp>
#include <App/V8/Tree/ModelInstance.hpp>

#include <OGRE/Ogre.h>

#include <vector>

namespace RNR
{
    class Camera;

    class Workspace : public ModelInstance
    {
    public:
        Workspace();

        virtual std::string getClassName() { return "Workspace"; }
        virtual void onChildAdded(RNR::Instance* childAdded);
        virtual void onChildRemoved(RNR::Instance* childRemoved);
        
        Camera* getCurrentCamera() const;
	    void setCurrentCamera(Camera *value); 
    private:
        bool m_instancingEnabled;
        std::vector<Ogre::InstancedEntity*> m_objects;
        Ogre::InstanceManager* m_instMan;
        Ogre::SceneNode* m_worldspawn;

        std::shared_ptr<Camera> currentCamera;
    };
}
