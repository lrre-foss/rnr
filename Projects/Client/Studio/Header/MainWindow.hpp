#pragma once

#include <App/V8/Tree/Instance.hpp>

#include <QMainWindow>
#include <QTreeWidget>
#include <QTimer>
#include <QToolBar>
#include <QMenuBar>
#include <QGridLayout>
#include <QTreeView>
#include <QVariant>
#include <PropertyViewer.hpp>

#include <OGRE/Bites/OgreBitesConfigDialog.h>
#include <OgreWidget.hpp>

#include "Resource/Studio.hpp"

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
        PropertyViewer* properties;

        void createToolbar();
        void updateTree(RNR::Instance* root_instance);

    public slots:
        void loadDatamodel();
        void selectInstance(QTreeWidgetItem *item, int column);
        void run();
        void pause();
    protected:
        void widgetItemPrepare(QTreeWidgetItem* item, RNR::Instance* instance);
        void recurseTreeAddInstance(QTreeWidgetItem* parent, RNR::Instance* instance);
        void closeEvent(QCloseEvent* event);
        void resizeEvent(QResizeEvent* event);
};