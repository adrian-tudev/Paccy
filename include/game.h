#ifndef GAME_H
#define GAME_H

#include "structs.h"

typedef struct Game {
  int score;
  Entity player;
} Game;

void game_init(Game* game);
void game_step(Game* game);
void game_cleanup(Game* game);

#endif
