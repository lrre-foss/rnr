#include <MainWindow.hpp>

MainWindow::MainWindow()
{
    QPixmap pixmap = QPixmap();
    pixmap.loadFromData(icon, icon_size);

    QWidget* content_widget = new QWidget();
    QGridLayout* grid = new QGridLayout();

    this->graphics_widget = new GL::Widget();
    grid->addWidget(this->graphics_widget, 0, 0, 1, 1);
    content_widget->setLayout(grid);

    setWindowTitle(QString("RNR Studio"));
    setWindowIcon(QIcon(pixmap));
    setCentralWidget(content_widget);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //
}