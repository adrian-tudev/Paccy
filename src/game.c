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

  /*
  for (int i = 0; i < MAX_GHOSTS; i++) {
    game->ghosts[i] = (Ghost*) malloc(sizeof(Ghost));
    // handle heap allocation failure
    if (game->ghosts[i] == NULL) {
      return false;
    }
  }*/

  // Initialize ghost 0
  game->ghosts[0] = (Ghost*) malloc(sizeof(Ghost));
  game->ghosts[0]->entity.pos.x = 1;
  game->ghosts[0]->entity.pos.y = 1;
  game->ghosts[0]->entity.dir.x = 0;
  game->ghosts[0]->entity.dir.y = 1;
  game->ghosts[0]->color.r = 255;
  game->ghosts[0]->color.g = 0;
  game->ghosts[0]->color.b = 0;

  for (int i = 1; i < MAX_GHOSTS; i++) {
    game->ghosts[i] = NULL;
  }
  
  // TODO load map from file and initialize player position accordingly
  // something like world = load_world("res/map.txt");
  static const char* world[] = {
  "#################################",
  "#                               #",
  "#                               #",
  "# ############################# #",
  "#                               #",
  "#            G                  #",
  "# ############################# #",
  "#                               #",
  "#             G                 #",
  "# ############################# #",
  "#                               #",
  "#                               #",
  "#                 G             #",
  "# ############################# #",
  "#        G                      #",
  "# ############################# #",
  "#                               #",
  "#                 P             #",
  "#   #######  ###                #",
  "#                               #",
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

static void move_entity(Entity* entity, const char** world) {
  Vec2 next_pos = {.x = entity->pos.x + entity->dir.x, .y = entity->pos.y + entity->dir.y};
  if (!onObstacle(next_pos, world)) {
    entity->pos = next_pos;
  }
}

void game_step(Game* game) {
  Entity* player = &game->player;
  move_entity(player, game->world);

  for (int i = 0; i < MAX_GHOSTS; i++) {
    // check for NULL exceptions
    if (game->ghosts[i] != NULL) {
      move_entity(&game->ghosts[i]->entity, game->world);
    }
  }
}

void game_cleanup(Game* game) {
  printf("Exiting...\n");
}
