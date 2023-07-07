#pragma once

#include <QMainWindow>
#include <client/common/RBXNUGraphicsWidget.hpp>

class StudioWindow : public QMainWindow
{
    Q_OBJECT

    public:
        StudioWindow();

    protected:
        void closeEvent(QCloseEvent* event);
};