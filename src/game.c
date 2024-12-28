#include "game.h"
#include <stdio.h>

void game_init(Game* game) {
  // TODO: load position from world
  game->player.pos.x = 5;
  game->player.pos.y = 5;

  // better way to init?
  game->player.dir.x = 1;
  game->player.dir.y = 0;
}

void game_step(Game* game) {
  Entity* player = &game->player;
  player->pos.x += player->dir.x;
  player->pos.y += player->dir.y;
  printf("x: %d, y: %d\n", player->pos.x, player->pos.y);
}

