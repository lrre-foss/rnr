#include "studiowindow.hpp"

StudioWindow::StudioWindow()
{
    setWindowTitle(QString("RBXNu Studio"));
    setWindowIcon(QIcon(":/content/images/icon.png"));

    studio_graphic_timer.start();
}

void StudioWindow::closeEvent(QCloseEvent* event)
{

}