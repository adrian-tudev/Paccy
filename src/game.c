#include "game.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int get_world_width(const char** world) {
  if (world == NULL || world[0] == NULL) {
    return 0;
  }
  return strlen(world[0]);
}

int get_world_height(const char** world) {
  int height = 0;
  while (world[height] != NULL) {
    height++;
  }
  return height;
}

static Vec2 load_player_pos(const char** world) {
  Vec2 pos = {-1, -1};
  for (int i = 0; i < get_world_height(world); i++) {
    for (int j = 0; j < get_world_width(world); j++) {
      if (world[i][j] == 'P') {
        pos.x = j;
        pos.y = i;
        return pos;
      }
    }
  }
  return pos;
}

static Ghost** load_ghosts(const char** world) {
  Ghost** ghosts = (Ghost**) malloc(sizeof(Ghost*) * MAX_GHOSTS);
  for (int i = 0; i < MAX_GHOSTS; i++) {
    ghosts[i] = NULL;
  }
  Color ghost_colors[] = {
    {255, 0, 0}, 
    {0, 255, 0},
    {0, 0xF5, 0xFF},
    {255, 255, 0}
  };

  int idx = 0;
  for (int i = 0; i < get_world_height(world); i++) {
    for (int j = 0; j < get_world_width(world); j++) {
      if (world[i][j] == 'G') {
        ghosts[idx] = NULL;
        ghosts[idx] = (Ghost*) malloc(sizeof(Ghost));
        ghosts[idx]->entity.pos = (Vec2){.x = j, .y = i};
        ghosts[idx]->entity.dir = (Vec2){.x = 0, .y = 1};
        ghosts[idx]->color = ghost_colors[idx];
        idx++;
      }
    }
  }
  return ghosts;
}

static int get_max_coins(const char** world) {
  int num_coins = 0;
  for (int i = 0; i < get_world_height(world); i++) {
    for (int j = 0; j < get_world_width(world); j++) {
      if (world[i][j] == ' ') {
        num_coins++;
      }
    }
  }
  return num_coins;
}

static Entity** load_coins(const char** world) {
  int num_coins = get_max_coins(world);
  Entity** coins = (Entity**) malloc(sizeof(Entity*) * num_coins);

  int idx = 0;
  for (int i = 0; i < get_world_height(world); i++) {
    for (int j = 0; j < get_world_width(world); j++) {
      if (world[i][j] == ' ') {
          coins[idx] = NULL;
          coins[idx] = (Entity*) malloc(sizeof(Entity));
          coins[idx]->pos = (Vec2){.x = j, .y = i};
          coins[idx]->dir = (Vec2){.x = 0, .y = 0};
          idx++;
      }
    }
  }
  assert(idx == num_coins);
  return coins;
}

static bool onObstacle(Vec2 pos, const char** world) {
  if (world[pos.y][pos.x] == '#')
    return true;
  return false;
}

static void move_entity(Entity* entity, const char** world, int WIDTH, int HEIGHT) {
  Vec2 next_pos = {.x = (entity->pos.x + entity->dir.x) % WIDTH, .y = (entity->pos.y + entity->dir.y) % HEIGHT};
  if (next_pos.x < 0) {
    next_pos.x = WIDTH - 1;
  }
  if (next_pos.y < 0) {
    next_pos.y = HEIGHT - 1;
  }
  if (!onObstacle(next_pos, world)) {
    entity->pos = next_pos;
  }
}

bool game_init(Game* game) {
  // TODO load map from file and initialize player position accordingly
  // something like world = load_world("res/map.txt");
  static const char* world[] = {
    "##################",
    "#   #        #   #",
    "# #   ##  ##   # #",
    "# ##          ## #",
    "#  #   #  #   #  #",
    "## ## #GGGG# ## ##",
    "P     ######      ",
    "## ##        ## ##",
    "## #####  ##### ##",
    "#   ##      ##   #",
    "# #    ####    # #",
    "#   ##      ##   #",
    "##################",
  };

  game->world = world;
  game->WIDTH = get_world_width(world);
  game->HEIGHT = get_world_height(world);

  game->player.pos = load_player_pos(game->world);
  game->player.dir = (Vec2){.x = 1, .y = 0};

  game->ghosts = load_ghosts(game->world);

  game->MAX_COINS = get_max_coins(game->world);
  game->coins = load_coins(game->world);

  game->score = 0;

  return true;
}

static void update_coins(Game* game) {
  for (int i = 0; i < game->MAX_COINS; i++) {
    if (game->coins[i] != NULL) {
      if (game->player.pos.x == game->coins[i]->pos.x && game->player.pos.y == game->coins[i]->pos.y) {
        free(game->coins[i]);
        game->coins[i] = NULL;
        game->score++;
        printf("Score: %d\n", game->score);
      }
    }
  }
}

void game_step(Game* game) {
  Entity* player = &game->player;
  move_entity(player, game->world, game->WIDTH, game->HEIGHT);
  update_coins(game);

  for (int i = 0; i < MAX_GHOSTS; i++) {
    // check for NULL exceptions
    if (game->ghosts[i] != NULL) {
      move_entity(&game->ghosts[i]->entity, game->world, game->WIDTH, game->HEIGHT);
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
