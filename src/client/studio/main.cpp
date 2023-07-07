#include <stdio.h>

#include <QApplication>
#include "studiowindow.hpp"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    StudioWindow window = StudioWindow();
    
    window.show();

    return a.exec();
}