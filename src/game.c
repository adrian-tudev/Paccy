#include "game.h"
#include "utils.h"
#include <stdio.h>
#include <SDL3/SDL.h>

bool game_init(Game* game) {
  game->world = (const char**) load_world("res/maps/map.txt");
  game->WIDTH = get_world_width(game->world);
  game->HEIGHT = get_world_height(game->world);

  game->player.pos = player_load_pos(game->world, TILE_SIZE);
  game->player.dir = (Vec2){.x = 1, .y = 0};
  game->player.speed = PLAYER_SPEED;

  game->ghosts = ghost_load(game->world, TILE_SIZE);

  game->MAX_COINS = get_max_coins(game->world);
  game->coins = load_coins(game->world);

  game->score = 0;

  return true;
}

static void update_coins(Game* game) {
  // iterate over coins and check if player is on coin
  for (int i = 0; i < game->MAX_COINS; i++) {
    if (game->coins[i] != NULL) {
      SDL_Rect coin_rect = {game->coins[i]->pos.x * TILE_SIZE, game->coins[i]->pos.y * TILE_SIZE, COIN_SIZE, COIN_SIZE};
      SDL_Rect player_rect = {game->player.pos.x, game->player.pos.y, TILE_SIZE, TILE_SIZE};
      if (SDL_HasRectIntersection(&coin_rect, &player_rect)) {
        free(game->coins[i]);
        game->coins[i] = NULL;
        game->score++;
      }
    }
  }
}

void game_step(Game* game) {
  entity_move(&game->player, game->world, game->WIDTH, game->HEIGHT, TILE_SIZE);
  update_coins(game);

  for (int i = 0; i < MAX_GHOSTS; i++) {
    // check if ghost exists
    if (game->ghosts[i] != NULL) {
      // if ghost has hit a wall or obstacle, generate a new direction
      if (!entity_valid_move(&game->ghosts[i]->entity, game->world, game->WIDTH, game->HEIGHT, TILE_SIZE)) {
        game->ghosts[i]->entity.dir = ghost_gen_move(game->ghosts[i]->entity, game->world, game->WIDTH, game->HEIGHT);
      }
      entity_move(&game->ghosts[i]->entity, game->world, game->WIDTH, game->HEIGHT, TILE_SIZE);
    }
  }
}

void game_cleanup(Game* game) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (game->ghosts[i] != NULL) {
      free(game->ghosts[i]);
    }
  }
  free(game->ghosts);

  for (int i = 0; i < game->MAX_COINS; i++) {
    if (game->coins[i] != NULL) {
      free(game->coins[i]);
    }
  }
  free(game->coins);

  printf("exiting...\n");
}