#pragma once

#include <App/InputManager.hpp>
#include <QMouseEvent>
#include <QKeyEvent>

namespace RNR
{
    class OgreWidget;

    class QtInputManager : public RNR::IInputManager
    {
    private:
        QPointF last_position;
        OgreWidget* widget;
        bool reset;
    public:
        QtInputManager(OgreWidget* widget);

        void keyEvent(QKeyEvent* e);
        void mouseEvent(QMouseEvent* e);

        virtual void resetMouse();
    };
}
