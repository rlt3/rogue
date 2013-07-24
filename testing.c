#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "Game.h"
#include "Render.h"
#include "Entity.h"
#include "Location.h"

void main_loop(Game *game);
void handle_input(SDLKey key, Entity *player, bool *gameOn);
void move_all_entities(Entity entities[], int currentFloor);

int main(int argc, char **argv) {
  static Game game;

  load_window(&game.screen);
  load_frames(game.frames);
  load_sprites(game.sprites);

  game.level = 1;
  game.frame = 0;
  game.time  = SDL_GetTicks();
  game.on    = true;

  create_dungeon(game.entities, game.level);

  main_loop(&game);

  return EXIT_SUCCESS;
}

void main_loop(Game *game) {
  SDL_Event event;

  while (game->on) {
    update_game((SDL_GetTicks() - game->time), game);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          handle_input(event.key.keysym.sym, &PLAYER, &game->on);
      }
    }

    move_all_entities(game->entities, game->level);
    render(game);
  }
}

void handle_input(SDLKey key, Entity *player, bool *gameOn) {
  switch(key) {
  case SDLK_ESCAPE: case SDL_QUIT:
    *gameOn = false;
    break;

  case SDLK_w: case SDLK_UP: case SDLK_k:
    update_entity(player, WALK_UP);
    break;

  case SDLK_a: case SDLK_LEFT: case SDLK_h:
    update_entity(player, WALK_LEFT);
    break;

  case SDLK_s: case SDLK_DOWN: case SDLK_j:
    update_entity(player, WALK_DOWN);
    break;

  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
    update_entity(player, WALK_RIGHT);
    break;

  case SDLK_SPACE:
    update_entity(player, ATTACKING);
    break;

  default:
    break;
  }
}

void move_all_entities(Entity entities[], int currentFloor) {
  for(int i=0; i<=currentFloor; i++) {
    if (!are_same_location(entities[i].location, entities[i].destination)) {
      move_entity(&entities[i], entities, currentFloor);
    }
  }
}
