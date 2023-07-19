#include <App/GUI/TopMenuBar.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    TopMenuBar::TopMenuBar(World* world)
    {
        m_world = world;

        Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
        material->getTechnique(0)->getPass(0)->createTextureUnitState("textures/placeholder.png");
        material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, Ogre::ColourValue(0.5, 0.5, 0.5));
        material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, 0.5f);
        material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SceneBlendType::SBT_TRANSPARENT_COLOUR);

        Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager->createOverlayElement("Panel", "TopMenuBarPanel"));
        panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(0,0);
        panel->setDimensions(128 * 5, 20);
        panel->setMaterial(material);

        Ogre::ColourValue text_color = Ogre::ColourValue(0.25, 0.25, 0.25);

        Ogre::TextAreaOverlayElement* toolsTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TopMenuBarTools"));
        toolsTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        toolsTextArea->setPosition(0, 0);
        toolsTextArea->setDimensions(128, 24);
        toolsTextArea->setCaption("Tools");
        toolsTextArea->setCharHeight(24);
        toolsTextArea->setFontName("ComicSans");
        toolsTextArea->setColour(text_color);

        Ogre::TextAreaOverlayElement* insertTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TopMenuBarInsert"));
        insertTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        insertTextArea->setPosition(128, 0);
        insertTextArea->setDimensions(128, 24);
        insertTextArea->setCaption("Insert");
        insertTextArea->setCharHeight(24);
        insertTextArea->setFontName("ComicSans");
        insertTextArea->setColour(text_color);

        Ogre::TextAreaOverlayElement* fullscreenTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TopMenuBarFullscreen"));
        fullscreenTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        fullscreenTextArea->setPosition(128*2, 0);
        fullscreenTextArea->setDimensions(128, 24);
        fullscreenTextArea->setCaption("Fullscreen");
        fullscreenTextArea->setCharHeight(24);
        fullscreenTextArea->setFontName("ComicSans");
        fullscreenTextArea->setColour(text_color);

        Ogre::TextAreaOverlayElement* helpTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TopMenuBarHelp"));
        helpTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        helpTextArea->setPosition(128*3, 0);
        helpTextArea->setDimensions(128, 24);
        helpTextArea->setCaption("Help...");
        helpTextArea->setCharHeight(24);
        helpTextArea->setFontName("ComicSans");
        helpTextArea->setColour(text_color);

        Ogre::TextAreaOverlayElement* exitTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "TopMenuBarExit"));
        exitTextArea->setMetricsMode(Ogre::GMM_PIXELS);
        exitTextArea->setPosition(128*4, 0);
        exitTextArea->setDimensions(128, 24);
        exitTextArea->setCaption("Exit");
        exitTextArea->setCharHeight(24);
        exitTextArea->setFontName("ComicSans");
        exitTextArea->setColour(text_color);

        panel->addChild(toolsTextArea);
        panel->addChild(insertTextArea);
        panel->addChild(fullscreenTextArea);
        panel->addChild(helpTextArea);
        panel->addChild(exitTextArea);

        m_debugText = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "DebugTextArea"));
        m_debugText->setMetricsMode(Ogre::GMM_PIXELS);
        m_debugText->setPosition(0, 300);
        m_debugText->setDimensions(420, 500);
        m_debugText->setCaption("Debug text!");
        m_debugText->setCharHeight(16);
        m_debugText->setFontName("ComicSans");
        m_debugText->setColour(Ogre::ColourValue(0.5f,0.f,0.5f));

        panel->addChild(m_debugText);

        Ogre::Overlay* overlay = overlayManager->create("OverlayName");
        overlay->add2D(panel);
        overlay->setZOrder(500);

        overlay->show();
    }

    void TopMenuBar::frame()
    {
        Workspace* workspace = m_world->getWorkspace();

        char debugtext[512];
        char render_debugtext[255];
        switch(workspace->m_batchMode)
        {
            case BATCH_INSTANCED:
                snprintf(render_debugtext, 255, "using BATCH_INSTANCED");
                break;
            case BATCH_STATIC_GEOMETRY:
                snprintf(render_debugtext, 255, "using BATCH_STATIC_GEOMETRY\nGeom Regions: %i", workspace->m_geom->getRegions().size());
                break;
        }
        snprintf(debugtext, 512, "Render\nLast DT = %f\n%s\n",m_world->getLastDelta(),render_debugtext,m_world->getOgreSceneManager());
        m_debugText->setCaption(debugtext);
    }
}