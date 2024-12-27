#include "error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void sdl_error() {
  printf("SDL_ERROR: %s", SDL_GetError());
}

void img_error() {
  printf("IMG_ERROR: %s", IMG_GetError());
}

