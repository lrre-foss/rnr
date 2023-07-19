#include <App/InputManager.hpp>
#include <App/V8/DataModel/Camera.hpp>
#include <stdio.h>

namespace RNR
{
    IInputManager::IInputManager()
    {
        state.mouse_primary = false;
        state.mouse_secondary = false;
        state.mouse_middle = false;
        state.mouse_scroll = 0;
    }

    void IInputManager::keyDown(int scancode)
    {

    }

    void IInputManager::keyUp(int scancode)
    {

    }

    void IInputManager::mouseMoveAbsolute(float x, float y)
    {

    }

    void IInputManager::mouseMoveRelative(float x, float y)
    {
        if(m_world)
        {
            float xd = x * m_world->getLastDelta();
            float yd = y * m_world->getLastDelta();

            Workspace* workspace = m_world->getWorkspace();
            Camera* camera = workspace->getCurrentCamera();
            if(camera && state.mouse_secondary)
            {
                camera->cameraFrame(xd, yd);

                resetMouse();
            }
        }
    }

    void IInputManager::mousePrimaryState(bool down)
    {
        state.mouse_primary = down;
    }

    void IInputManager::mouseSecondaryState(bool down)
    {
        state.mouse_secondary = down;
    }

    void IInputManager::mouseMiddleState(bool down)
    {
        state.mouse_middle = down;
    }

    void IInputManager::mouseScrollState(float scroll)
    {
        state.mouse_scroll = scroll;
    }
}