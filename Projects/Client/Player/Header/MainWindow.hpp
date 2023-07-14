#pragma once

#include <QMainWindow>

#include "Resource/Player.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

    protected:
        void closeEvent(QCloseEvent* event);
};