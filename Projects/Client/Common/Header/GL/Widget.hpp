#pragma once

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <glad/glad.h>

#include <GL/Adorn.hpp>

namespace GL
{
    class Widget : public QOpenGLWidget
    {
        Q_OBJECT

        public:
            Widget(QWidget* parent = nullptr);

            double delta;

            Adorn* adorn;

        protected:
            virtual void initialize();
            virtual void paint();
            virtual void resize(int x, int y);

        private:
            QElapsedTimer timer;
    };
}
