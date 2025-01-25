#ifndef GHOST_H
#define GHOST_H

#include "structs.h"

typedef struct Ghost {
  Entity entity;
  Color color;
} Ghost;

// GHOST controller gives the ghost the next direction
Vec2 move_ghost(const char** world, int WIDTH, int HEIGHT, Entity ghost);

#endif