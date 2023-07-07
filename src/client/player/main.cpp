#include <stdio.h>

#include <QApplication>

#include <client/player/PlayerWindow.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    PlayerWindow window = PlayerWindow();
    
    window.show();

    return app.exec();
}