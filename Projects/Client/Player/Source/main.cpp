#include <stdio.h>
#include <filesystem>

#include <QApplication>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    if (!fs::is_directory("ShaderCache") || !fs::exists("ShaderCache"))
        fs::create_directory("ShaderCache");
    }

    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();

    return app.exec();
}