#pragma once

#include <glad/glad.h>
#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <client/common/Adorn.hpp>

class RNRGraphicsWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    RNRGraphicsWidget(QWidget* parent = nullptr);

    double delta_time;

    GL::Adorn* gl_adorn;
protected:
    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
private:
    QElapsedTimer timer;
};