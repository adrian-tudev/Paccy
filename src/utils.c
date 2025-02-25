#include <SDL3/SDL.h>

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

bool on_obstacle(Vec2 pos, const char** world, int TILE_SIZE) {
  int w = get_world_width(world);
  int h = get_world_height(world);

  // iterate over every wall and check if player is colliding
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (world[i][j] == '#') {
        SDL_Rect tile = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_Rect player_rect = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
        if (SDL_HasRectIntersection(&tile, &player_rect)) {
          return true;
        }
      }
    }
  }

  return false;
}

// calculate next position according to dir
Vec2 step_pos(Vec2 pos, Vec2 dir, int WIDTH, int HEIGHT, int SPEED) {
  Vec2 next_pos = {.x = pos.x + dir.x * SPEED, .y = pos.y + dir.y * SPEED};
  return next_pos;
}

bool entity_valid_move(const Entity* entity, const char** world, int WIDTH, int HEIGHT, int TILE_SIZE) {
  Vec2 next_pos = step_pos(entity->pos, entity->dir, WIDTH, HEIGHT, entity->speed);
  return !on_obstacle(next_pos, world, TILE_SIZE);
}

// TODO: should wrap around if out of bounds
void entity_move(Entity* entity, const char** world, int WIDTH, int HEIGHT, int TILE_SIZE) {
  
  // wrap around on x axis
  if (entity->pos.x >= WIDTH * TILE_SIZE) {
    entity->pos.x = 0;
  } else if (entity->pos.x + TILE_SIZE <= 0) {
    entity->pos.x = WIDTH * TILE_SIZE - TILE_SIZE;
  }

  // wrap around on y axis
  if (entity->pos.y >= HEIGHT * TILE_SIZE) {
    entity->pos.y = 0;
  } else if (entity->pos.y + TILE_SIZE <= 0) {
    entity->pos.y = HEIGHT * TILE_SIZE - TILE_SIZE;
  }

  if (entity_valid_move(entity, world, WIDTH, HEIGHT, TILE_SIZE)) {
    entity->pos = step_pos(entity->pos, entity->dir, WIDTH, HEIGHT, entity->speed);
  }
}

Vec2 player_load_pos(const char** world, int TILE_SIZE) {
  Vec2 pos = {-1, -1};
  for (int i = 0; i < get_world_height(world); i++) {
    for (int j = 0; j < get_world_width(world); j++) {
      if (world[i][j] == 'P') {
        pos.x = j * TILE_SIZE;
        pos.y = i * TILE_SIZE;
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