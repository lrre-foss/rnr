#include <MainWindow.hpp>
#include <QFile>
#include <QFileDialog>
#include <App/V8/Tree/ModelInstance.hpp>

MainWindow::MainWindow()
{
    QPixmap pixmap = QPixmap();
    pixmap.loadFromData(icon, icon_size);

    QWidget* content_widget = new QWidget();
    QGridLayout* grid = new QGridLayout();

    ogreRoot = new Ogre::Root();
    Ogre::ConfigDialog* config = OgreBites::getNativeConfigDialog();
    ogreRoot->showConfigDialog(config);

    ogreRoot->initialise(false);
    
    menubar = new QMenuBar();
    grid->addWidget(menubar, 0, 0, 1, 2);

    toolbar = new QToolBar();
    grid->addWidget(toolbar, 1, 0, 1, 2);

    createToolbar();

    this->ogreWidget = new RNR::OgreWidget(ogreRoot);
    grid->addWidget(this->ogreWidget, 2, 0, 1, 2);
    
    explorer = new QTreeWidget();
    connect(explorer, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(selectInstance(QTreeWidgetItem*, int)));
    grid->addWidget(explorer, 2, 2, 1, 1);

    content_widget->setLayout(grid);

    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);
    setWindowTitle(QString("RNR Studio"));
    setWindowIcon(QIcon(pixmap));
    setCentralWidget(content_widget);
}

void MainWindow::widgetItemPrepare(QTreeWidgetItem* item, RNR::Instance* instance)
{
    QString icon_path;
    icon_path = "content/textures/studio/icons/";
    icon_path += instance->getClassName();
    icon_path += ".png";
    QIcon icon;
    if(QFile::exists(icon_path))
        icon = QIcon(icon_path);
    else
        icon = QIcon("content/textures/studio/icons/Instance.png");
    item->setIcon(0, icon);
}

void MainWindow::selectInstance(QTreeWidgetItem *item, int column)
{
    RNR::Instance* instance = item->data(0, Qt::UserRole).value<RNR::Instance*>();
    if(dynamic_cast<RNR::ModelInstance*>(instance))
    {
        ogreWidget->selectedInstance = instance;
    }
}

void MainWindow::recurseTreeAddInstance(QTreeWidgetItem* parent, RNR::Instance* instance)
{
    for(auto& child : *instance->getChildren())
    {
        QTreeWidgetItem* instance_w = new QTreeWidgetItem();
        widgetItemPrepare(instance_w, child);
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

        widgetItemPrepare(parent, child);
        recurseTreeAddInstance(parent, child);
        explorer->addTopLevelItem(parent);
    }
}

void MainWindow::loadDatamodel()
{
    this->ogreWidget->world->load(QFileDialog::getOpenFileName(this, tr("Open RBXL"), tr(""), tr("RBXLs (*.rbxl)")).toLocal8Bit().data());

    updateTree(ogreWidget->world->getDatamodel());
}

void MainWindow::createToolbar()
{
    QMenu* file_menu = menubar->addMenu("File");
    QAction* load_action = file_menu->addAction("Load", this, SLOT(loadDatamodel()));
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