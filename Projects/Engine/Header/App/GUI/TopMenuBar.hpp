#pragma once

#include <OGRE/Ogre.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlay.h>

namespace RNR
{
    class World;

    class TopMenuBar 
    {
        Ogre::TextAreaOverlayElement* m_debugText;
        World* m_world;
    public:
        TopMenuBar(World* world);

        void frame();
    }; 
}