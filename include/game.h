#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "structs.h"

typedef struct Game {
  int score;
  Entity player;
  const char** world;
} Game;

bool game_init(Game* game);
void game_step(Game* game);
void game_cleanup(Game* game);

#endif
