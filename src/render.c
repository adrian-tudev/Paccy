#include <SDL3/SDL.h>

#include "render.h"
#include "error.h"

#define BLACK   0,    0   , 0
#define WHITE   0xFF, 0xFF, 0xFF
#define RED     0xFF, 0,    0
#define YELLOW  0xFF, 0xFF, 0
#define BLUE    0,    0   , 0xFF

#define EXPAND_COLOR(color) color.r, color.g, color.b

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

static int frame = 0; 
static int animation_speed = 50;

static void render_player(Entity* player) {
  static Vec2 prev_player_dir = {0, 0};
  SDL_Surface* player_surf = IMG_Load("res/sprites/player.png");
  if (player_surf == NULL)
    printf("Couldn't load player sprite: %s\n", SDL_GetError());

  SDL_Texture* player_tex = SDL_CreateTextureFromSurface(renderer, player_surf);
  if (player_tex == NULL) {
    printf("Couldn't create texture from surface: %s\n", SDL_GetError());
  }

  static int animation_counter = 0;
  // Calculate source rectangle based on current frame
  SDL_FRect srcrect = {animation_counter * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
  SDL_FRect dstrect = {player->pos.x, player->pos.y, TILE_SIZE, TILE_SIZE}; // Destination rectangle

  // Calculate angle based on player direction
  double angle = atan2(player->dir.y, player->dir.x) * 180 / 3.14159265;
  SDL_RenderTextureRotated(renderer, player_tex, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
  SDL_DestroySurface(player_surf);
  SDL_DestroyTexture(player_tex);

  frame++;
  if (frame % animation_speed == 0) {
    animation_counter++;
    animation_counter %= 4;
  }
  prev_player_dir = player->pos;
}

static void render_ghosts(Ghost** ghosts) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (ghosts[i] != NULL) {
      render_rect(&(SDL_FRect){ghosts[i]->entity.pos.x, ghosts[i]->entity.pos.y,
       TILE_SIZE, TILE_SIZE}, EXPAND_COLOR(ghosts[i]->color));
    }
  }
}

static void render_coins(Entity** coins, int MAX_COINS) {
  for (int i = 0; i < MAX_COINS; i++) {
    if (coins[i] != NULL) {
      render_rect(&(SDL_FRect){coins[i]->pos.x * TILE_SIZE + (TILE_SIZE / 2) - COIN_SIZE / 2, coins[i]->pos.y * TILE_SIZE + (TILE_SIZE / 2) - COIN_SIZE / 2,
       COIN_SIZE, COIN_SIZE}, YELLOW);
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
