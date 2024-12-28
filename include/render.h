#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "structs.h"

void render_world(SDL_Renderer* renderer, const char** world, int width, int height);

void render_player(SDL_Renderer* renderer, Entity* player);

#endif
