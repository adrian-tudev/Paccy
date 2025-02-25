#include "input.h"

Vec2 nxt_dir = {0, 0};

void handle_input(Core* core, Game* game) {
  // initialize first frame
  if (nxt_dir.x == 0 && nxt_dir.y == 0)
    nxt_dir = game->player.dir;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      core->state = EXIT;
    }
    if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode) {
        case SDL_SCANCODE_UP:
          nxt_dir = (Vec2) {0, -1};
          break;

        case SDL_SCANCODE_DOWN:
          nxt_dir= (Vec2) {0, 1};
          break;

        case SDL_SCANCODE_RIGHT:
          nxt_dir = (Vec2) {1, 0};
          break;

        case SDL_SCANCODE_LEFT:
          nxt_dir = (Vec2) {-1, 0};
          break;

        default:
          break;
      }
    }

  }
  // store move until valid
  Entity temp = game->player;
  temp.dir = nxt_dir;
  if (entity_valid_move(&temp, game->world, game->WIDTH, game->HEIGHT, TILE_SIZE)) {
    game->player = temp;
  }
}
