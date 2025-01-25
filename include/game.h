#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "structs.h"
#include "ghost.h"

#define MAX_GHOSTS 4

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
