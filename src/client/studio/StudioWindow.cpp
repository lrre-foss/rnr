#include <client/studio/StudioWindow.hpp>
#include <QGridLayout>
#include "studio_rsc.h"

StudioWindow::StudioWindow()
{
    setWindowTitle(QString("RBXNU Studio"));

    QPixmap icon_pixmap = QPixmap();
    icon_pixmap.loadFromData(icon_png, icon_png_size);
    
    QWidget *content_widget = new QWidget();
    QGridLayout* grid = new QGridLayout();

    this->graphics_widget = new RBXNUGraphicsWidget();

    grid->addWidget(this->graphics_widget, 0, 0, 1, 1);

    content_widget->setLayout(grid);
    setCentralWidget(content_widget);
    setWindowIcon(QIcon(icon_pixmap));
}

void StudioWindow::closeEvent(QCloseEvent* event)
{

}