#pragma once

#include <glad/glad.h>
#include <QOpenGLWidget>
#include <QElapsedTimer>

class RBXNUGraphicsWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    RBXNUGraphicsWidget(QWidget* parent = nullptr);

    double delta_time;
protected:
    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
private:
    QElapsedTimer timer;
};