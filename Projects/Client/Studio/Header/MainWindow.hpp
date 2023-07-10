#pragma once

#include <QMainWindow>
#include <QTreeWidget>
#include <QTimer>
#include <QToolBar>
#include <QMenuBar>

#include <GL/Widget.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

        Ogre::Root* ogreRoot;
        GL::Widget* widget;
        QTreeWidget* explorer;
        QToolBar* toolbar;
        QMenuBar* menubar;

        void createToolbar();
    protected:
        void closeEvent(QCloseEvent* event);
        void resizeEvent(QResizeEvent* event);
};