#include <client/common/RBXNUGraphicsWidget.hpp>

RBXNUGraphicsWidget::RBXNUGraphicsWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    gl_adorn = new GL::Adorn();
}

void RBXNUGraphicsWidget::initializeGL()
{
    printf("qt_common: initializeGL\n");

    if(gladLoadGL()) {
        printf("gl: initialized\n");
    }
}

void RBXNUGraphicsWidget::paintGL()
{
    this->delta_time = ((double)timer.elapsed())/1000.0;
    timer.start();
}

void RBXNUGraphicsWidget::resizeGL(int w, int h)
{
    printf("qt_common: resizeGL %i %i\n", w, h);
}