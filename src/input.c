#include "input.h"

void handle_input(Core* core, Game* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      core->state = EXIT;
    }
    if (event.type == SDL_EVENT_KEY_DOWN) {
      switch (event.key.scancode) {
        case SDL_SCANCODE_UP:
          game->player.dir = (Vec2) {0, -1};
          break;

        case SDL_SCANCODE_DOWN:
          game->player.dir = (Vec2) {0, 1};
          break;

        case SDL_SCANCODE_RIGHT:
          game->player.dir = (Vec2) {1, 0};
          break;

        case SDL_SCANCODE_LEFT:
          game->player.dir = (Vec2) {-1, 0};
          break;

        default:
          break;
      }
    }
  }
}
