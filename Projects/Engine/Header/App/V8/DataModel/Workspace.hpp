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

        void buildGeom();
        
        Camera* getCurrentCamera() const;
	    void setCurrentCamera(Camera *value); 
    private:
        void buildGeomInstance(Instance* instance);

        bool m_geomDirty;
        Ogre::StaticGeometry* m_geom; 
        Ogre::SceneNode* m_worldspawn;
        Ogre::Entity* m_partEntity;

        std::shared_ptr<Camera> currentCamera;
    };
}
