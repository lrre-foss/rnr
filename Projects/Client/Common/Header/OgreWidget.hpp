#pragma once

#include <glad/glad.h>

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QElapsedTimer>
#include <QResizeEvent>
#include <OGRE/Ogre.h>
#include <OGRE/RTShaderSystem/OgreShaderGenerator.h>

#include <GL/Adorn.hpp>

namespace RNR
{
    class OgreWidget : public QWidget
    {
        Q_OBJECT

        public:
            OgreWidget(Ogre::Root *root, QWidget* parent = nullptr);

            double delta;
            double render_time;

            Adorn* adorn;
            
            Ogre::Root* ogreRoot;
            Ogre::RenderWindow* ogreWindow;
            Ogre::SceneManager* ogreSceneManager;
            Ogre::Camera* ogreCamera;
            Ogre::RTShader::ShaderGenerator* ogreShaderGen;

            void render();
            void initializeOgre();

            Ogre::NameValuePairList getRenderOptions();
            Ogre::String getWindowHandle();

        protected:
            virtual void paintEvent(QPaintEvent* pEvent);
            virtual void resizeEvent(QResizeEvent* rEvent);
            virtual void mouseMoveEvent(QMouseEvent *event);
            virtual void closeEvent(QCloseEvent* event);
            virtual QPaintEngine* paintEngine() const;
            
        private:
            QElapsedTimer timer;
    };
}
