#include <SDL2/SDL.h>
#include "render.h"

#define TILE_SIZE 32
#define WHITE 255, 255, 255
#define YELLOW 255, 255, 0

void render_world(SDL_Renderer* renderer, const char** world, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      SDL_Rect r = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
      if (world[i][j] == '#') {
        SDL_SetRenderDrawColor(renderer, WHITE, 255);
      }

      if (world[i][j] != ' ')
        SDL_RenderFillRect(renderer, &r);
    }
  }
}

void render_player(SDL_Renderer* renderer, Entity* player) {
  SDL_SetRenderDrawColor(renderer, YELLOW, 255);
  SDL_Rect r = {player->pos.x * TILE_SIZE, player->pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
  printf("x\n");
  SDL_RenderFillRect(renderer, &r);
}
