#include <stdio>

#include <QApplication>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();

    return app.exec();
}