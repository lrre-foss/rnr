#include <client/studio/StudioWindow.hpp>
#include "studio_rsc.h"

StudioWindow::StudioWindow()
{
    setWindowTitle(QString("RBXNU Studio"));

    QPixmap icon_pixmap = QPixmap();
    icon_pixmap.loadFromData(icon_png, icon_png_size);

    setWindowIcon(QIcon(icon_pixmap));
}

void StudioWindow::closeEvent(QCloseEvent* event)
{

}