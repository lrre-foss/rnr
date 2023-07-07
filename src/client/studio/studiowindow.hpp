#ifndef __CLIENT_STUDIO_STUDIOWINDOW_HPP__
#define __CLIENT_STUDIO_STUDIOWINDOW_HPP__

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

#endif