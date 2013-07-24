#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "Render.h"
#include "Entity.h"
#include "Location.h"

#define TOTAL_ENTITIES    16
#define PLAYER            entities[0]

void create_dungeon(Entity entities[], int dungeonFloor);

void game_loop(SDL_Surface *screen, SDL_Surface *sprites[], 
               SDL_Rect frames[8][2], Entity entities[],
               int dungeonFloor);

void update_game(unsigned dt, unsigned *time, 
                 unsigned short *frameToDraw, Entity entities[]);

void handle_input(SDLKey key, Entity *player, bool *running);


int main(int argc, char **argv) {
  static SDL_Surface    *screen;
  static SDL_Surface    *sprites[TOTAL_ENTITIES];
  static SDL_Rect       frames[8][2];
  static Entity         entities[TOTAL_ENTITIES];

  int dungeonFloor      = 0;
  screen                = load_window();

  load_animations(sprites, frames);
  create_dungeon(entities, dungeonFloor);
  game_loop(screen, sprites, frames, entities, dungeonFloor);

  return EXIT_SUCCESS;
}

void create_dungeon(Entity entities[], int dungeonFloor) {
  Location location = {100, 100};
  Entity player = (Entity){0, IDLE, 10, 0, location, location, true};
  entities[0] = player;
}

void game_loop(SDL_Surface *screen, SDL_Surface *sprites[], 
               SDL_Rect frames[8][2], Entity entities[],
               int dungeonFloor) {
  SDL_Event event;

  unsigned short int frameToDraw      = 0;
  unsigned time                       = SDL_GetTicks();
  bool running                        = true;

  while (running) {
    update_game((SDL_GetTicks() - time), &time, &frameToDraw, entities);

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          handle_input(event.key.keysym.sym, &PLAYER, &running);
      }
    }

    render(screen, entities, sprites, frames, frameToDraw);
  }
}

void update_game(unsigned dt, unsigned *time, 
                 unsigned short *frameToDraw, Entity entities[]) {
  if(dt >= 250) {
    *time = SDL_GetTicks();

    *frameToDraw = *frameToDraw ? 0 : 1;

    if(PLAYER.frames > 0) {
      PLAYER.frames -= 1;

      if(PLAYER.frames == 0) {
        PLAYER.state -= PLAYER.state > 3 ? 4 : 0;
      }
    } else {
      PLAYER.idle = true;
    }

  }
}

void handle_input(SDLKey key, Entity *player, bool *running) {
  switch(key) {
  case SDLK_ESCAPE: case SDL_QUIT:
    *running = false;
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
