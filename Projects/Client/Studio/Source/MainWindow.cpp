#include <MainWindow.hpp>
#include <QGridLayout>
#include <QTreeView>
#include <QToolBar>

#include "Resources/StudioResources.hpp"

MainWindow::MainWindow()
{
    QPixmap pixmap = QPixmap();
    pixmap.loadFromData(icon, icon_size);

    QWidget* content_widget = new QWidget();
    QGridLayout* grid = new QGridLayout();

    ogreRoot = new Ogre::Root();
    ogreRoot->showConfigDialog(NULL);
    ogreRoot->initialise(false);
    this->widget = new GL::Widget(ogreRoot);
    grid->addWidget(this->widget, 0, 0, 1, 2);
    QTreeView* instance_tree = new QTreeView();
    grid->addWidget(instance_tree, 0, 2, 1, 1);
    
    content_widget->setLayout(grid);

    grid->setContentsMargins(0,0,0,0);
    grid->setSpacing(0);

    setWindowTitle(QString("RNR Studio"));
    setWindowIcon(QIcon(pixmap));
    setCentralWidget(content_widget);

    QToolBar* tool_bar = new QToolBar(this);
}

void MainWindow::closeEvent(QCloseEvent* event)
{

}