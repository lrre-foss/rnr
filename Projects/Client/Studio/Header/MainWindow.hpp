#pragma once

#include <App/V8/Tree/Instance.hpp>

#include <QMainWindow>
#include <QTreeWidget>
#include <QTimer>
#include <QToolBar>
#include <QMenuBar>

#include <OgreWidget.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();

        Ogre::Root* ogreRoot;
        RNR::OgreWidget* ogreWidget;
        QTreeWidget* explorer;
        QToolBar* toolbar;
        QMenuBar* menubar;

        void createToolbar();
        void updateTree(RNR::Instance* root_instance);

    protected:
        void recurseTreeAddInstance(QTreeWidgetItem* parent, RNR::Instance* instance);
        void closeEvent(QCloseEvent* event);
        void resizeEvent(QResizeEvent* event);
};