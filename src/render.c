#include <SDL3/SDL.h>

#include "render.h"

#define WHITE 255, 255, 255
#define YELLOW 255, 255, 0

static void render_world(SDL_Renderer* renderer, const char** world, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      SDL_FRect r = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
      if (world[i][j] == '#') {
        SDL_SetRenderDrawColor(renderer, WHITE, 255);
        SDL_RenderFillRect(renderer, &r);
      }
    }
  }
}

static void render_player(SDL_Renderer* renderer, Entity* player) {
  SDL_SetRenderDrawColor(renderer, YELLOW, 255);
  SDL_FRect r = {player->pos.x * TILE_SIZE, player->pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
  SDL_RenderFillRect(renderer, &r);
}

// rendering logic
void render(SDL_Renderer* renderer, Game* game) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);

  render_world(renderer, game->world, 33, 20);
  render_player(renderer, &game->player);

  SDL_RenderPresent(renderer);
}
