#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "structs.h"
#include "ghost.h"

#define MAX_GHOSTS 4

typedef struct Game {
  int score;
  Entity player;
  Ghost* ghosts[MAX_GHOSTS];
  const char** world;
} Game;

bool game_init(Game* game);
void game_step(Game* game);
void game_cleanup(Game* game);

#endif
