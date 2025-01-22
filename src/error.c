#include "error.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

void sdl_error() {
  printf("SDL_ERROR: %s", SDL_GetError());
}
