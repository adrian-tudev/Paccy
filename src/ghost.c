#include <stdlib.h>

#include "structs.h"
#include "ghost.h"

Ghost** load_ghosts(const char** world) {
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

Vec2 move_ghost(const char** world, int WIDTH, int HEIGHT, Entity ghost) {
  Vec2 choices[3];
  int cnt = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      // generates a list of possible directions for the ghost to move (not opposite of current direction)
      if ((i == 0 || j == 0) && ghost.dir.x != -i && ghost.dir.y != -j) {
        choices[cnt++] = (Vec2){.x = i, .y = j};
      }
    }
  }

  int final_choices = 0;
  Vec2 selectable_choices[3];
  for (int i = 0; i < cnt; i++) {
    Vec2 prev_pos = ghost.pos;
    ghost.dir = choices[i];
    move_entity(&ghost, world, WIDTH, HEIGHT);

    if (ghost.pos.x == prev_pos.x && ghost.pos.y == prev_pos.y) {
      choices[i] = (Vec2){.x = 0, .y = 0};
      continue;
    }
    selectable_choices[final_choices++] = choices[i];
  }
  // if no choices forward, go back
  if (final_choices == 0)
    return (Vec2){.x = -ghost.dir.x, .y = -ghost.dir.y};

  return selectable_choices[rand() % final_choices];
}
