#pragma once

#include <QMainWindow>
#include <QTreeWidget>
#include <QTimer>

#include <GL/Widget.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

        GL::Widget* widget;
        QTreeWidget* explorer;

    protected:
        void closeEvent(QCloseEvent* event);
}