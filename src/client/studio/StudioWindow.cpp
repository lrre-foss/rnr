#include <client/studio/StudioWindow.hpp>

StudioWindow::StudioWindow()
{
    setWindowTitle(QString("RBXNU Studio"));
    setWindowIcon(QIcon(":/content/images/icon.png"));
}

void StudioWindow::closeEvent(QCloseEvent* event)
{

}