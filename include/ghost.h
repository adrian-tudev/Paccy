#ifndef GHOST_H
#define GHOST_H

#include "structs.h"

#define MAX_GHOSTS 4

typedef struct Ghost {
  Entity entity;
  Color color;
} Ghost;

/* 
Ghost controller gives the next direction.
Should randomly pick a direction except backwards
*/
Vec2 move_ghost(const char** world, int WIDTH, int HEIGHT, Entity ghost);
Ghost** load_ghosts(const char** world);

#endif