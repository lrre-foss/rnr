#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

    protected:
        void closeEvent(QCloseEvent* event);
}