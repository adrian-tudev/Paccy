#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>

#include "game.h"
#include "structs.h"

#define TILE_SIZE 32

void render_init(SDL_Window* win);
void render(Game* game);

#endif
