#include <App/GUI/TopMenuBar.hpp>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlayContainer.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlay.h>

namespace RNR
{
    TopMenuBar::TopMenuBar()
    {
        Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("placeholder.png");
        material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, 0.5f);
        material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, Ogre::ColourValue(1.0, 1.0, 1.0));
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager->createOverlayElement("Panel", "PanelName"));
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(0,0);
        panel->setDimensions(320, 24);
        panel->setMaterial(material);

        Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TextAreaName"));
        textArea->setMetricsMode(Ogre::GMM_PIXELS);
        textArea->setPosition(0, 0);
        textArea->setDimensions(320, 24);
        textArea->setCaption("Hello, World!");
        textArea->setCharHeight(24);
        textArea->setFontName("ComicSans");
        textArea->setColour(Ogre::ColourValue(0.f,0.f,0.f));

        Ogre::Overlay* overlay = overlayManager->create("OverlayName");
        overlay->add2D(panel);
        overlay->setZOrder(500);

        panel->addChild(textArea);

        overlay->show();
    }
}