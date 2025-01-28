#include "game.h"
#include "utils.h"
#include <stdio.h>

bool game_init(Game* game) {
  // TODO load map from file and initialize player position accordingly
  // something like world = load_world("res/map.txt");
  static const char* world[] = {
    "##################",
    "#   #        #   #",
    "# #   ##  ##   # #",
    "# ##          ## #",
    "#  #   #  #   #  #",
    "## ## #GGGG# ## ##",
    "P     ######      ",
    "## ##        ## ##",
    "## #####  ##### ##",
    "#   ##      ##   #",
    "# #    ####    # #",
    "#   ##      ##   #",
    "##################",
  };

  game->world = world;
  game->WIDTH = get_world_width(world);
  game->HEIGHT = get_world_height(world);

  game->player.pos = load_player_pos(game->world);
  game->player.dir = (Vec2){.x = 1, .y = 0};

  game->ghosts = load_ghosts(game->world);

  game->MAX_COINS = get_max_coins(game->world);
  game->coins = load_coins(game->world);

  game->score = 0;

  return true;
}

static void update_coins(Game* game) {
  for (int i = 0; i < game->MAX_COINS; i++) {
    if (game->coins[i] != NULL) {
      if (game->player.pos.x == game->coins[i]->pos.x && game->player.pos.y == game->coins[i]->pos.y) {
        free(game->coins[i]);
        game->coins[i] = NULL;
        game->score++;
        printf("Score: %d\n", game->score);
      }
    }
  }
}

void game_step(Game* game) {
  Entity* player = &game->player;
  move_entity(player, game->world, game->WIDTH, game->HEIGHT);
  update_coins(game);

  for (int i = 0; i < MAX_GHOSTS; i++) {
    // check for NULL exceptions
    if (game->ghosts[i] != NULL) {
      Vec2 gen_ghost_move = move_ghost(game->world, game->WIDTH, game->HEIGHT, game->ghosts[i]->entity);
      game->ghosts[i]->entity.dir = gen_ghost_move;
      move_entity(&game->ghosts[i]->entity, game->world, game->WIDTH, game->HEIGHT);
    }
  }
}

void game_cleanup(Game* game) {
  for (int i = 0; i < MAX_GHOSTS; i++) {
    if (game->ghosts[i] != NULL) {
      free(game->ghosts[i]);
    }
  }
  free(game->ghosts);

  for (int i = 0; i < game->MAX_COINS; i++) {
    if (game->coins[i] != NULL) {
      free(game->coins[i]);
    }
  }
  free(game->coins);

  printf("exiting...\n");
}
