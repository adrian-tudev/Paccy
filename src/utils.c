#include <assert.h>
#include <stdio.h>
#include "utils.h"

#define MAX_LINE_LENGTH 256

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

char** load_world(const char* file_name) {
  FILE* file = fopen(file_name, "r");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }

  char** world = NULL;
  char line[MAX_LINE_LENGTH];
  int height = 0;

  while (fgets(line, sizeof(line), file)) {
    // Remove newline character if present
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }

    world = realloc(world, (height + 1) * sizeof(char*));
    world[height] = strdup(line);
    height++;
  }

  fclose(file);

  // Add a NULL terminator to the array
  world = realloc(world, (height + 1) * sizeof(char*));
  world[height] = NULL;

  return world;
}

bool onObstacle(Vec2 pos, const char** world) {
  if (world[pos.y][pos.x] == '#')
    return true;
  return false;
}

// wrap around if position goes out of bounds
Vec2 step_pos(Vec2 pos, Vec2 dir, int WIDTH, int HEIGHT) {
  Vec2 next_pos = {.x = (pos.x + dir.x) % WIDTH, .y = (pos.y + dir.y) % HEIGHT};
  if (next_pos.x < 0) {
    next_pos.x = WIDTH - 1;
  }
  if (next_pos.y < 0) {
    next_pos.y = HEIGHT - 1;
  }
  return next_pos;
}

void move_entity(Entity* entity, const char** world, int WIDTH, int HEIGHT) {
  Vec2 next_pos = step_pos(entity->pos, entity->dir, WIDTH, HEIGHT);

  if (!onObstacle(next_pos, world)) {
    entity->pos = next_pos;
  }
}

Vec2 load_player_pos(const char** world) {
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

int get_max_coins(const char** world) {
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

Entity** load_coins(const char** world) {
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