#include <GL/Widget.hpp>

namespace GL
{
    Widget::Widget(QWidget* parent) : QOpenGLWidget(parent)
    {
        this->adorn = new GL::Adorn();
    }

    void Widget::initialize()
    {
        printf("RNR::GLWidget::initialize: initializing\n");

        if (gladLoadGL())
        {
            printf("RNR::GLWidget::initialize: initialized\n");
        }
    }

    void Widget::paint()
    {
        this->delta = ((double)this->timer.elapsed()) / 1000.0;
        this->timer.start();
    }

    void Widget::resize(int x, int y)
    {
        printf("RNR::GLWidget::resize: resizing to (%i, %i)\n", x, y);
    }
}