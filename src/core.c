#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "error.h"
#include "game.h"
#include "render.h"

Game game;

void core_init(Core* core) {
  core->state = INIT;

  core->win_width = 1440;
  core->win_height = 1080;
  core->fps = 6;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    sdl_error();

  int img_init_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_init_flags) & img_init_flags))
    img_error();

  core->window = SDL_CreateWindow("Paccy", 
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      core->win_width, core->win_height, SDL_WINDOW_SHOWN);

  if (core->window == NULL)
    sdl_error();

  core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_ACCELERATED);

  if (core->renderer == NULL)
    sdl_error();

  // core is owner of game, should call cleanup()
  if (!game_init(&game)) {
    printf("Couldn't initialize the game!\n");
    exit(-1);
  }
}

void core_run(Core* core) {
  core->state = RUNNING;

  Uint32 elapsed = 0;
  printf("run.\n");
  

  while (core->state == RUNNING) {
    Uint32 start = SDL_GetTicks();

    // INPUT
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        core->state = EXIT;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
          case SDL_SCANCODE_UP:
            game.player.dir.x = 0;
            game.player.dir.y = -1;
            break;

          case SDL_SCANCODE_DOWN:
            game.player.dir.x = 0;
            game.player.dir.y = 1;
            break;

          case SDL_SCANCODE_RIGHT:
            game.player.dir.x = 1;
            game.player.dir.y = 0;
            break;

          case SDL_SCANCODE_LEFT:
            game.player.dir.x = -1;
            game.player.dir.y = 0;
            break;

          default:
            break;
        }
      }
    }

    // UPDATE according to FPS
    if (elapsed >= 1000 / core->fps) {
      game_step(&game);
      elapsed = 0;
    }

    // RENDER
    render(core->renderer, &game);

    Uint32 end = SDL_GetTicks();
    Uint32 frame_duration = end - start;
    elapsed += frame_duration;
    // cap_fps(elapsed, core->fps);
  }
}

void core_exit(Core* core) {
  core->state = CLEANUP;

  game_cleanup(&game);
  SDL_DestroyRenderer(core->renderer);
  SDL_DestroyWindow(core->window);

  IMG_Quit();
  SDL_Quit();
}

