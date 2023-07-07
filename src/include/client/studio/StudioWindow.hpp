#pragma once

#include <QMainWindow>
#include <QTreeWidget>
#include <client/common/RBXNUGraphicsWidget.hpp>
#include <QTimer>

class StudioWindow : public QMainWindow
{
    Q_OBJECT

    public:
        StudioWindow();

        RBXNUGraphicsWidget* graphics_widget;
        QTreeWidget* datamodel_tree;
    protected:
        void closeEvent(QCloseEvent* event);
};