#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structs.h"

// miscellaneous helper functions for the main game logic ig (should maybe be refactored into player and coin files etc.)

int get_world_width(const char** world);
int get_world_height(const char** world);
void move_entity(Entity* entity, const char** world, int WIDTH, int HEIGHT);
bool onObstacle(Vec2 pos, const char** world);
Vec2 load_player_pos(const char** world);
Vec2 step_pos(Vec2 pos, Vec2 dir, int WIDTH, int HEIGHT);
int get_max_coins(const char** world);
Entity** load_coins(const char** world);