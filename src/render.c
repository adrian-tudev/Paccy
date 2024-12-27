#include <SDL2/SDL.h>
#include "render.h"

static char** load_map(const char* file_path) {
  const int MAX_LINE = 100;
  const int MAX_LINE_LENGTHS = 256;

  FILE* file = fopen(file_path, "r");
  if (!file) {
    printf("Error opening a file brodie (%s)", file_path);
    return NULL;
  }

  char** lines = malloc(MAX_LINES
}

void render_world(const char* file_path) {
  load_map(file_path);

}
