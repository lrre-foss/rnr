#pragma once

#include <QMainWindow>
#include <QOpenGLWidget>

class StudioWindow : public QMainWindow
{
    Q_OBJECT

    public:
        StudioWindow();

    protected:
        void closeEvent(QCloseEvent* event);
};