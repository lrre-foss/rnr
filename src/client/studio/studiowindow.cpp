#include "studiowindow.hpp"

StudioWindow::StudioWindow()
{
    setWindowTitle(QString("RBXNu Studio"));
    setWindowIcon(QIcon(":/content/images/icon.png"));
}

void StudioWindow::closeEvent(QCloseEvent* event)
{

}