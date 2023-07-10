#include <stdio.h>

#include <QApplication>
#include <QSurfaceFormat>
#include <QStatusBar>
#include <App/V8/World/World.hpp>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(0);

    QSurfaceFormat::setDefaultFormat(format);
    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();
    window.ogreWidget->initializeOgre();

    RNR::World* world = new RNR::World();
    Ogre::SceneNode* workspace_node = window.ogreWidget->ogreSceneManager->createSceneNode("Workspace");
    workspace_node->attachObject(world->getWorkspace());
    workspace_node->setVisible(true);
    printf("main: workspace = %p (%p)\n",workspace_node, world->getWorkspace());
    window.updateTree(world->getDatamodel());

    while (window.isVisible())
    {
        window.statusBar()->showMessage(QString::asprintf("Dt=%f, Rt=%f", window.ogreWidget->delta, window.ogreWidget->render_time));
        app.processEvents();
        window.ogreWidget->render();
        world->preStep();
        world->step(window.ogreWidget->delta);
        world->update();
    }
}