#include <MainWindow.hpp>
#include <QGridLayout>
#include <QTreeView>
#include <QVariant>

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
    grid->addWidget(menubar, 0, 0, 1, 2);

    toolbar = new QToolBar();
    grid->addWidget(toolbar, 1, 0, 1, 2);

    createToolbar();

    this->ogreWidget = new RNR::OgreWidget(ogreRoot);
    grid->addWidget(this->ogreWidget, 2, 0, 1, 2);
    
    explorer = new QTreeWidget();
    grid->addWidget(explorer, 2, 2, 1, 1);

    content_widget->setLayout(grid);

    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);

    setWindowTitle(QString("RNR Studio"));
    setWindowIcon(QIcon(pixmap));
    setCentralWidget(content_widget);
}

void MainWindow::recurseTreeAddInstance(QTreeWidgetItem* parent, RNR::Instance* instance)
{
    for(auto& child : *instance->getChildren())
    {
        QTreeWidgetItem* instance_w = new QTreeWidgetItem();
        instance_w->setText(0, QString(child->getName().c_str()));
        instance_w->setData(0, Qt::UserRole, QVariant::fromValue(child));
        recurseTreeAddInstance(instance_w, child);
        parent->addChild(instance_w);
    }
}

void MainWindow::updateTree(RNR::Instance* root_instance)
{
    for(auto& child : *root_instance->getChildren())
    {
        QTreeWidgetItem* parent = new QTreeWidgetItem();
        parent->setData(0, Qt::UserRole, QVariant::fromValue(child));
        parent->setText(0, QString(child->getName().c_str()));

        recurseTreeAddInstance(parent, child);
        explorer->addTopLevelItem(parent);
    }
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