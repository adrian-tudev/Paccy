#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO load map file into "world" variable before passing it to the renderer
static char** load_world(const char* file_path) {

  return NULL;
}

bool game_init(Game* game) {
  // TODO: load position from world
  game->player.pos.x = 5;
  game->player.pos.y = 5;

  // better way to init?
  game->player.dir.x = 1;
  game->player.dir.y = 0;
  
  // TODO load map from file and initialize player position accordingly
  //world = load_world("res/map.txt");
  static const char* world[] = {
  "#################################",
  "#                               #",
  "# ############################# #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#   #######  ###                #",
  "#          P                    #",
  "#################################",
  };
  game->world = world;

  return true;
}

static bool onObstacle(Vec2 pos, const char** world) {
  if (world[pos.y][pos.x] == '#')
    return true;

  return false;
}

void game_step(Game* game) {
  Entity* player = &game->player;

  Vec2 next_pos = {.x = player->pos.x + player->dir.x, .y = player->pos.y + player->dir.y};
  if (!onObstacle(next_pos, game->world)) {
    player->pos = next_pos;
  }
}

void game_cleanup(Game* game) {

}
