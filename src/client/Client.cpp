#include <Logger.hpp>
#include <v8tree/Instance.hpp>

#include <v8datamodel/DataModel.hpp>
#include <pipeline/View.hpp>

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int sr = SDL_Init(SDL_INIT_VIDEO);
  if (sr) {
    DEV_LOGMSGF("SDL_Init returned %s", SDL_GetError());
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window =
      SDL_CreateWindow("RNR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_OPENGL);
  if (!window) {
    DEV_LOGMSGF("SDL_CreateWindow returned %s", SDL_GetError());
    return -1;
  }

  SDL_GLContext glcontext = SDL_GL_CreateContext(window);
  if (!glcontext) {
    DEV_LOGMSGF("SDL_GL_CreateContext returned %s", SDL_GetError());
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    DEV_LOGMSGF("gladLoadGLLoader failed");
    return -1;
  }

  RNR::DataModel* datamodel = new RNR::DataModel();
  RNR::Rendering::View* view = new RNR::Rendering::View();
  view->setModel(datamodel);

  DEV_LOGMSGF("opengl version: %s", glGetString(GL_VERSION));
  DEV_LOGMSGF("opengl renderer: %s", glGetString(GL_RENDERER));
  DEV_LOGMSGF("opengl vendor: %s", glGetString(GL_VENDOR));
  DEV_LOGMSGF("opengl shading language version: %s",
              glGetString(GL_SHADING_LANGUAGE_VERSION));

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }

    view->frame();
    SDL_GL_SwapWindow(window);
  }

  DEV_LOGMSGF("goodbye");

  return 0;
}