#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include "core.h"
#include "error.h"
#include "game.h"
#include "render.h"
#include "input.h" 

Game game;

void core_init(Core* core) {
  core->state = INIT;

  core->win_width = 1440;
  core->win_height = 1080;
  core->fps = 6;

  if (!SDL_Init(SDL_INIT_VIDEO))
    sdl_error();

  core->window = SDL_CreateWindow("Paccy", 
      core->win_width, core->win_height, 0);

  if (core->window == NULL)
    sdl_error();

  // core is owner of game, should call cleanup()
  if (!game_init(&game)) {
    printf("Couldn't initialize the game!\n");
  }

  // let render module create renderer
  render_init(core->window);
}

void core_run(Core* core) {
  core->state = RUNNING;

  Uint32 elapsed = 0;
  printf("run.\n");
  
  while (core->state == RUNNING) {
    Uint32 start = SDL_GetTicks();

    // INPUT
    handle_input(core, &game);

    // UPDATE according to FPS
    if (elapsed >= 1000 / core->fps) {
      game_step(&game);
      elapsed = 0;
    }

    // RENDER
    render(&game);

    // FRAME RATE
    Uint32 end = SDL_GetTicks();
    Uint32 frame_duration = end - start;
    elapsed += frame_duration;
  }
}

void core_exit(Core* core) {
  core->state = CLEANUP;

  game_cleanup(&game);
  SDL_DestroyRenderer(core->renderer);
  SDL_DestroyWindow(core->window);

  SDL_Quit();
}

