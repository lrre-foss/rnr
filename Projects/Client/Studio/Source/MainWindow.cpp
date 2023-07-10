#include <MainWindow.hpp>
#include <QGridLayout>
#include <QTreeView>

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
    
    menubar = new QMenuBar();
    grid->addWidget(menubar, 0, 0, 1, 1);

    toolbar = new QToolBar();
    grid->addWidget(toolbar, 1, 0, 1, 1);

    createToolbar();

    this->widget = new GL::Widget(ogreRoot);
    grid->addWidget(this->widget, 2, 0, 1, 2);
    
    explorer = new QTreeWidget();
    grid->addWidget(explorer, 2, 2, 1, 1);

    content_widget->setLayout(grid);

    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);


    setWindowTitle(QString("RNR Studio"));
    setWindowIcon(QIcon(pixmap));
    setCentralWidget(content_widget);
}

void MainWindow::createToolbar()
{
    QMenu* file_menu = menubar->addMenu("File");
    QMenu* help_menu = menubar->addMenu("Help");
    help_menu->addAction("About...");
}

void MainWindow::closeEvent(QCloseEvent* event)
{

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QSize new_size = event->size();
    explorer->setMaximumWidth(new_size.width()/4);

}