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

#ifdef FORCE_ENABLE_VSYNC
    format.setSwapInterval(1);
#else
    format.setSwapInterval(0);
#endif

    QSurfaceFormat::setDefaultFormat(format);
    QApplication app(argc, argv);
    MainWindow window = MainWindow();

    window.show();
    window.ogreWidget->initializeOgre();

    RNR::World* world = new RNR::World(window.ogreWidget->ogreRoot, window.ogreWidget->ogreSceneManager);
    window.updateTree(world->getDatamodel());
    window.ogreWidget->world = world;

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