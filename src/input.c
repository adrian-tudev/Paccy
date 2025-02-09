#include "input.h"

Vec2 nxt_dir;

void handle_input(Core* core, Game* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      core->state = EXIT;
    }
    if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode) {
        case SDL_SCANCODE_UP:
          nxt_dir = (Vec2) {0, -1};
          game->player.dir = nxt_dir;
          break;

        case SDL_SCANCODE_DOWN:
          nxt_dir= (Vec2) {0, 1};
          game->player.dir = nxt_dir;
          break;

        case SDL_SCANCODE_RIGHT:
          nxt_dir = (Vec2) {1, 0};
          game->player.dir = nxt_dir;
          break;

        case SDL_SCANCODE_LEFT:
          nxt_dir = (Vec2) {-1, 0};
          game->player.dir = nxt_dir;
          break;

        default:
          break;
      }
    }

    /*
    // store move until valid
    Entity temp = game->player;
    temp.dir = nxt_dir;
    if (entity_valid_move(&temp, game->world, game->WIDTH, game->HEIGHT)) {
      game->player = temp;
    }*/
  }
}
