#include <stdio.h>
#include <filesystem>

#include <QApplication>
#include <QSurfaceFormat>
#include <QStatusBar>
#include <App/V8/World/World.hpp>

#include <MainWindow.hpp>

int main(int argc, char** argv)
{
    if (!std::filesystem::is_directory("ShaderCache") || !std::filesystem::exists("ShaderCache")) {
        std::filesystem::create_directory("ShaderCache");
    }

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
    window.ogreWidget->setWorld(world);

    while (window.isVisible())
    {
        window.statusBar()->showMessage(QString::asprintf("Dt=%f, Rt=%f, FPS=%f", window.ogreWidget->delta, window.ogreWidget->render_time, 1 / window.ogreWidget->delta));
        app.processEvents();
        window.ogreWidget->render();
        world->preStep();
        world->step(window.ogreWidget->delta);
        world->update();
    }
}