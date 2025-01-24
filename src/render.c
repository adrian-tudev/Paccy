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

static int get_world_width(const char** world) {
  if (world == NULL || world[0] == NULL) {
    return 0;
  }
  return strlen(world[0]);
}

static int get_world_height(const char** world) {
  int height = 0;
  while (world[height] != NULL) {
    height++;
  }
  return height;
}

static void render_world(const char** world) {
  int width = get_world_width(world);
  int height = get_world_height(world);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
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

void render_init(SDL_Window* win) {
  renderer = SDL_CreateRenderer(win, NULL);
  if (renderer == NULL)
    sdl_error();
}

// rendering logic
void render(Game* game) {
  SDL_SetRenderDrawColor(renderer, BLACK, 0xFF);
  SDL_RenderClear(renderer);

  render_world(game->world);
  render_player(&game->player);
  render_ghosts(game->ghosts);

  SDL_RenderPresent(renderer);
}
