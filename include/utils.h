#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structs.h"

// helper functions for the main game logic (maybe refactor into separate modules...)

// World

int get_world_width(const char** world);
int get_world_height(const char** world);
char** load_world(const char* file_name);

// Entity

void entity_move(Entity* entity, const char** world, int WIDTH, int HEIGHT);
bool entity_valid_move(const Entity* entity, const char** world, int WIDTH, int HEIGHT);
bool on_obstacle(const Vec2 pos, const char** world);
Vec2 player_load_pos(const char** world);
Vec2 step_pos(Vec2 pos, Vec2 dir, int WIDTH, int HEIGHT);

// Coins

int get_max_coins(const char** world);
Entity** load_coins(const char** world);