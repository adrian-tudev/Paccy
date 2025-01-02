#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#include "game.h"
#include "structs.h"

#define TILE_SIZE 32

void render(SDL_Renderer* renderer, Game* game);

#endif
