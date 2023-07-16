#include <OgreWidget.hpp>
#include <QApplication>

#include <OGRE/Bites/OgreSGTechniqueResolverListener.h>
#include <OGRE/OgreDefaultDebugDrawer.h>

#ifdef __unix__
#include <qpa/qplatformnativeinterface.h>
#include <X11/Xlib.h>
#endif

// credits to https://github.com/Ekman/Qt-Ogre-Widget
namespace RNR
{
    OgreWidget::OgreWidget(Ogre::Root *root, QWidget *parent) : QWidget(parent)
    {
        this->ogreRoot = root;
        this->setMinimumSize(640, 480);
        this->ogreWindow = NULL;

        this->setAttribute(Qt::WA_OpaquePaintEvent);
        this->setAttribute(Qt::WA_PaintOnScreen);
        this->setMouseTracking(true);
        this->setCursor(QCursor(Qt::BlankCursor));
        this->setFocusPolicy(Qt::StrongFocus);
    }

    void OgreWidget::initializeOgre()
    {
        Ogre::NameValuePairList options = this->getRenderOptions();

        printf("OgreWidget::initializeOgre: initializing render window\n");
        ogreWindow = ogreRoot->createRenderWindow("GLWidget-RenderWindow", width(), height(), false, &options);
        ogreWindow->setActive(true);
        ogreWindow->setVisible(true);
        ogreWindow->setAutoUpdated(true);
        
        Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("shaders", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        //Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("../Content/OgrePrivate/RTShaderLib/GLSL/", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME); // rtshader path
        //Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

        ogreSceneManager = ogreRoot->createSceneManager();
        ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.2f,0.2f,0.2f));

        Ogre::SceneNode* camNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 5);
        camNode->lookAt(Ogre::Vector3(0, sinf(render_time), cosf(render_time)), Ogre::Node::TS_PARENT);

        ogreCamera = ogreSceneManager->createCamera("myCam");
        ogreCamera->setNearClipDistance(0.1); // specific to this sample
        ogreCamera->setFarClipDistance(5000.f);
        ogreCamera->setAutoAspectRatio(true);
        ogreCamera->setFOVy(Ogre::Degree(70.f));
        camNode->attachObject(ogreCamera);

        ogreViewport = ogreWindow->addViewport(ogreCamera);

        if(Ogre::RTShader::ShaderGenerator::initialize())
        {
            ogreShaderGen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
            ogreShaderGen->setShaderCachePath("ShaderCache/");
            ogreShaderGen->addSceneManager(ogreSceneManager);

            OgreBites::SGTechniqueResolverListener* technique_resolver = new OgreBites::SGTechniqueResolverListener(ogreShaderGen);
            Ogre::MaterialManager::getSingleton().addListener(technique_resolver);

            printf("OgreWidget::initializeOgre: initialized ShaderGenerator successfully\n");   
        }
        else
            printf("OgreWidget::initializeOgre: unable to initialize ShaderGenerator\n");

        Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("content", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);        
        Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

        ogreSceneManager->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
        ogreSceneManager->setShadowFarDistance(500.f);

        Ogre::Light* light = ogreSceneManager->createLight("SunLight");
        Ogre::SceneNode* lightNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->setDirection(-0.25, -0.5, -0.5);
        lightNode->attachObject(light);

        light->setCastShadows(true);
        light->setDiffuseColour(0.9, 0.9, 1.0);
        light->setSpecularColour(1.0, 1.0, 1.0);
        light->setType(Ogre::Light::LT_DIRECTIONAL);

        Ogre::MaterialManager::getSingletonPtr()->reloadAll();
        Ogre::MaterialManager::getSingletonPtr()->load("sky/null_plainsky512", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        ogreSceneManager->setSkyBox(true, "sky/null_plainsky512");

        this->render_time = 0.0;
    }

    void OgreWidget::render()
    {
        if(!world)
            return;

        this->delta = ogreRoot->getTimer()->getMicroseconds() / 1000000.0;
        this->render_time += ogreRoot->getTimer()->getMilliseconds() / 1000.0;
        ogreRoot->getTimer()->reset();

        Ogre::AxisAlignedBox boundingBox = world->getWorkspace()->getBoundingBox();
        if(!boundingBox.isNull() && !boundingBox.isInfinite())
        {
            ogreCamera->getParentSceneNode()->setPosition(boundingBox.getCorner(Ogre::AxisAlignedBox::CornerEnum::NEAR_LEFT_TOP));
            ogreCamera->getParentSceneNode()->lookAt(boundingBox.getCenter(), Ogre::Node::TS_WORLD);
        }
        
        ogreRoot->renderOneFrame(this->delta);
    }

    Ogre::NameValuePairList OgreWidget::getRenderOptions()
    {
        Ogre::NameValuePairList options;

        options["externalWindowHandle"] = getWindowHandle();
        options["FSAA"] = "4";
#ifdef FORCE_ENABLE_VSYNC
        options["vsync"] = "true";
#endif
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        options["macAPI"] = "cocoa";
        options["macAPICocoaUseNSView"] = "true";
#endif 

        return options;
    }

    Ogre::String OgreWidget::getWindowHandle()
    {
        Ogre::String windowHandle;
        windowHandle = Ogre::StringConverter::toString((unsigned long)winId());
        printf("OgreWidget::getWindowHandle(): %s\n", windowHandle.c_str());
        return windowHandle;
    }

    void OgreWidget::resizeEvent(QResizeEvent *rEvent)
    {
        QWidget::resizeEvent(rEvent);
        if(ogreWindow)
        {
            QSize size = rEvent->size();
            ogreWindow->resize(size.width(), size.height());
        }
    }

    void OgreWidget::paintEvent(QPaintEvent *pEvent)
    {
        //
    }

    void OgreWidget::mouseMoveEvent(QMouseEvent *mEvent)
    {
    }

    void OgreWidget::closeEvent(QCloseEvent* event)
    {
        ogreWindow->destroy();
    }

    QPaintEngine* OgreWidget::paintEngine() const
    {
        return 0;
    }
}