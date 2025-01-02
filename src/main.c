#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "core.h"
#include "game.h"

int main() {
  printf("init.\n");
  Core core;
  core_init(&core);
  core_run(&core);
  core_exit(&core);

  return 0;
}
