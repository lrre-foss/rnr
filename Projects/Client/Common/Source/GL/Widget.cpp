#include <GL/Widget.hpp>
#include <QApplication>

#ifdef __unix__
#include <qpa/qplatformnativeinterface.h>
#include <X11/Xlib.h>
#endif

// credits to https://github.com/Ekman/Qt-Ogre-Widget
namespace GL
{
    Widget::Widget(Ogre::Root *root, QWidget *parent) : QWidget(parent)
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

    void Widget::initializeOgre()
    {
        Ogre::NameValuePairList options = this->getRenderOptions();

        printf("Widget::initializeOgre: initializing render window\n");
        ogreWindow = ogreRoot->createRenderWindow("GLWidget-RenderWindow", width(), height(), false, &options);
        ogreWindow->setActive(true);
        ogreWindow->setVisible(true);
        ogreWindow->setAutoUpdated(true);

        Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("content", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
        Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation("../Content", "FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);

        Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
        Ogre::MaterialManager::getSingletonPtr()->load("sky", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        ogreSceneManager = ogreRoot->createSceneManager();
        ogreSceneManager->setSkyBox(true, "sky/null_plainsky512", 5.f);
        ogreSceneManager->setAmbientLight(Ogre::ColourValue::White);

        //Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        //shadergen->addSceneManager(ogreSceneManager);

        Ogre::Light* light = ogreSceneManager->createLight("MainLight");
        Ogre::SceneNode* lightNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);

        Ogre::SceneNode* camNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 5);
        camNode->lookAt(Ogre::Vector3(0, sinf(render_time), cosf(render_time)), Ogre::Node::TS_PARENT);

        ogreCamera = ogreSceneManager->createCamera("myCam");
        ogreCamera->setNearClipDistance(0.1); // specific to this sample
        ogreCamera->setFarClipDistance(1000.f);
        ogreCamera->setAutoAspectRatio(true);
        camNode->attachObject(ogreCamera);

        ogreWindow->addViewport(ogreCamera);
        this->render_time = 0.0;
    }

    void Widget::render()
    {
        this->delta = ogreRoot->getTimer()->getMicroseconds() / 1000000.0;
        this->render_time += ogreRoot->getTimer()->getMilliseconds() / 1000.0;
        ogreRoot->getTimer()->reset();

        ogreCamera->getParentSceneNode()->lookAt(Ogre::Vector3(sinf(render_time)*5.f, cosf(render_time)*5.f, 0.f), Ogre::Node::TS_PARENT);

        ogreRoot->renderOneFrame(this->delta);
    }

    Ogre::NameValuePairList Widget::getRenderOptions()
    {
        Ogre::NameValuePairList options;

        options["externalWindowHandle"] = getWindowHandle();
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
        options["macAPI"] = "cocoa";
        options["macAPICocoaUseNSView"] = "true";
#endif 

        return options;
    }

    Ogre::String Widget::getWindowHandle()
    {
        Ogre::String windowHandle;
        windowHandle = Ogre::StringConverter::toString((unsigned long)window()->winId());
        printf("Widget::getWindowHandle(): %s\n", windowHandle.c_str());
        return windowHandle;
    }

    void Widget::resizeEvent(QResizeEvent *rEvent)
    {
        QWidget::resizeEvent(rEvent);
        if(ogreWindow)
        {
            QSize size = rEvent->size();
            ogreWindow->resize(size.width(), size.height());
        }
    }

    void Widget::paintEvent(QPaintEvent *pEvent)
    {
    }

    void Widget::mouseMoveEvent(QMouseEvent *mEvent)
    {
    }

    QPaintEngine *Widget::paintEngine() const
    {
        return 0;
    }
}