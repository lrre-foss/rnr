#include <Logger.hpp>
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int sr = SDL_Init(SDL_INIT_VIDEO);
  if (sr)
    DEV_LOGMSGF("SDL_Init returned %s", SDL_GetError());
}