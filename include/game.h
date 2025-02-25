#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "ghost.h"
#include "structs.h"
#include "utils.h"

#define TILE_SIZE 32
#define COIN_SIZE TILE_SIZE / 4
#define PLAYER_SPEED 2

typedef struct Game {
  int score;
  Entity player;
  Ghost** ghosts;
  Entity** coins;
  int MAX_COINS;
  const char** world;
  int WIDTH;
  int HEIGHT;
} Game;

bool game_init(Game* game);
void game_step(Game* game);
void game_cleanup(Game* game);

#endif