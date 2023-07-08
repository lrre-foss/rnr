#include <client/common/RNRGraphicsWidget.hpp>

RNRGraphicsWidget::RNRGraphicsWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    gl_adorn = new GL::Adorn();
}

void RNRGraphicsWidget::initializeGL()
{
    printf("qt_common: initializeGL\n");

    if(gladLoadGL()) {
        printf("gl: initialized\n");
    }
}

void RNRGraphicsWidget::paintGL()
{
    this->delta_time = ((double)timer.elapsed())/1000.0;
    timer.start();
}

void RNRGraphicsWidget::resizeGL(int w, int h)
{
    printf("qt_common: resizeGL %i %i\n", w, h);
}