#ifndef GHOST_H
#define GHOST_H

#include "structs.h"

#define MAX_GHOSTS 4
#define GHOST_SPEED 4

typedef struct Ghost {
  Entity entity;
  Color color;
} Ghost;

// loads all the ghosts from the world and returns a pointer
Ghost** ghost_load(const char** world, int TILE_SIZE);

/* 
Ghost controller gives the next direction.
Should randomly pick a direction except backwards
*/
Vec2 ghost_gen_move(Entity ghost, char** world, int WIDTH, int HEIGHT);


#endif