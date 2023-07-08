#include <stdio>

#include <QApplication>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(0);

    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();

    bool running = true;
    while (running)
    {
        app.processEvents();
        window.graphics_widget->update();
    }
}