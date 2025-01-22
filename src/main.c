#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_image.h>
#include "core.h"
#include "game.h"

int main(int argc, char* args[]) {
  printf("init.\n");
  Core core;
  core_init(&core);
  core_run(&core);
  core_exit(&core);

  return 0;
}
