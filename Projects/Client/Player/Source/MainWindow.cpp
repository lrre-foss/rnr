#include <MainWindow.hpp>
#include "Resources/PlayerResources.hpp"

MainWindow::MainWindow()
{
    QPixmap pixmap = QPixmap();
    pixmap.loadFromData(icon, icon_size);

    setWindowTitle(QString("RNR"));
    setWindowIcon(QIcon(pixmap));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //
}