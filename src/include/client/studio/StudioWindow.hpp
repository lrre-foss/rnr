#pragma once

#include <QMainWindow>
#include <QTreeWidget>
#include <client/common/RNRGraphicsWidget.hpp>
#include <QTimer>

class StudioWindow : public QMainWindow
{
    Q_OBJECT

    public:
        StudioWindow();

        RNRGraphicsWidget* graphics_widget;
        QTreeWidget* datamodel_tree;
    protected:
        void closeEvent(QCloseEvent* event);
};