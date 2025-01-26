#include <SDL3/SDL.h>

#include "render.h"
#include "error.h"

#define BLACK   0,    0   , 0
#define WHITE   0xFF, 0xFF, 0xFF
#define YELLOW  0xFF, 0xFF, 0
#define BLUE    0,    0   , 0xFF

#define COLOR_ARGS(color) color.r, color.g, color.b

SDL_Renderer* renderer = NULL;

static void render_rect(SDL_FRect* rect, int r, int g, int b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, rect);
}

static void render_world(const char** world, int WIDTH, int HEIGHT) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      SDL_FRect r = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
      if (world[i][j] == '#') {
        render_rect(&r, BLUE);
      }
    }
  }
}

static void render_player(Entity* player) {
  render_rect(&(SDL_FRect){player->pos.x * TILE_SIZE, player->pos.y * TILE_SIZE,
   TILE_SIZE, TILE_SIZE}, YELLOW);
}

static void render_ghosts(Ghost** ghosts) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (ghosts[i] != NULL) {
      render_rect(&(SDL_FRect){ghosts[i]->entity.pos.x * TILE_SIZE, ghosts[i]->entity.pos.y * TILE_SIZE,
       TILE_SIZE, TILE_SIZE}, COLOR_ARGS(ghosts[i]->color));
    }
  }
}

static void render_coins(Entity** coins, int MAX_COINS) {
  for (int i = 0; i < MAX_COINS; i++) {
    if (coins[i] != NULL) {
      int coin_size = TILE_SIZE / 8;
      render_rect(&(SDL_FRect){coins[i]->pos.x * TILE_SIZE + (TILE_SIZE / 2) - coin_size / 2, coins[i]->pos.y * TILE_SIZE + (TILE_SIZE / 2) - coin_size / 2,
       coin_size, coin_size}, WHITE);
    }
  }
}

void render_init(SDL_Window* win) {
  renderer = SDL_CreateRenderer(win, NULL);
  if (renderer == NULL)
    sdl_error();
}

// rendering logic
void render(Game* game) {
  SDL_SetRenderDrawColor(renderer, BLACK, 0xFF);
  SDL_RenderClear(renderer);

  render_world(game->world, game->WIDTH, game->HEIGHT);
  render_coins(game->coins, game->MAX_COINS);
  render_ghosts(game->ghosts);
  render_player(&game->player);

  // white border around arena
  SDL_SetRenderDrawColor(renderer, WHITE, 0xFF);
  SDL_RenderRect(renderer, &(SDL_FRect){0, 0, game->WIDTH * TILE_SIZE, game->HEIGHT * TILE_SIZE});

  SDL_RenderPresent(renderer);
}
