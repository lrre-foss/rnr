#include <stdio.h>
#include <filesystem>

#include <QApplication>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    if (!std::filesystem::is_directory("ShaderCache") || !std::filesystem::exists("ShaderCache")) {
        std::filesystem::create_directory("ShaderCache");
    }

    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();

    return app.exec();
}