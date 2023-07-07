#include <stdio.h>

#include <QApplication>

#include <client/studio/StudioWindow.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    StudioWindow window = StudioWindow();
    
    window.show();

    return app.exec();
}