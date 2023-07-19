#include <App/GUI/TopMenuBar.hpp>
#include <App/V8/World/World.hpp>

namespace RNR
{
    TopMenuBar::TopMenuBar(World* world)
    {
        m_world = world;

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

        m_debugText = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", "DebugTextArea"));
        m_debugText->setMetricsMode(Ogre::GMM_PIXELS);
        m_debugText->setPosition(0, 300);
        m_debugText->setDimensions(420, 500);
        m_debugText->setCaption("Debug text!");
        m_debugText->setCharHeight(24);
        m_debugText->setFontName("ComicSans");
        m_debugText->setColour(Ogre::ColourValue(0.5f,0.f,0.5f));


        Ogre::Overlay* overlay = overlayManager->create("OverlayName");
        overlay->add2D(panel);
        overlay->setZOrder(500);

        panel->addChild(textArea);

        panel->addChild(m_debugText);

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