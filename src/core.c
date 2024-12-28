#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core.h"
#include "error.h"
#include "game.h"
#include "render.h"

const char* world[] = {
  "#################################",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#                               #",
  "#          P                    #",
  "#################################",
};
Game game;

// TODO load map file into "world" variable before passing it to the renderer
static char** load_world(const char* file_path) {

}

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


  game_init(&game);
  // TODO load map from file
  //world = load_world("res/map.txt");
}

static void cap_fps(Uint32 elapsed, int fps) {
  Uint32 target = 1000 / fps;
  Uint32 wait = target - elapsed;
  SDL_Delay(wait);
}

void core_run(Core* core) {
  core->state = RUNNING;

  printf("run.\n");
  while (core->state == RUNNING) {
    Uint32 start = SDL_GetTicks();


    // INPUT
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        core->state = EXIT;
      }
    }

    // UPDATE
    game_step(&game);

    // RENDER
    // TODO: factor into a single function?
    SDL_SetRenderDrawColor(core->renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(core->renderer);
    render_world(core->renderer, world, 33, 20);
    render_player(core->renderer, &game.player);

    SDL_RenderPresent(core->renderer);

    Uint32 end = SDL_GetTicks();
    Uint32 elapsed = end - start;
    cap_fps(elapsed, core->fps);
  }
}

void core_exit(Core* core) {
  core->state = CLEANUP;
  SDL_DestroyRenderer(core->renderer);
  SDL_DestroyWindow(core->window);

  IMG_Quit();
  SDL_Quit();
}

