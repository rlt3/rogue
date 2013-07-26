#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

#define SCREENX           640
#define SCREENY           512

#define TOTAL_ENTITIES    16
#define PLAYER            game->entities[0]

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < SCREENX && y < SCREENY)


#include <SDL/SDL.h>
#include "Entity.h"

typedef struct Game {
  SDL_Surface    *screen;
  SDL_Surface    *sprites[TOTAL_ENTITIES];
  SDL_Rect       frames[8][2];
  Entity         entities[TOTAL_ENTITIES];

  uint32_t       time;
  uint8_t        frame;
  uint8_t        level;

  bool           on;
} Game;

void load_window(SDL_Surface **screen) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  atexit(SDL_Quit);

  *screen = SDL_GetVideoSurface();
}

void load_frames(SDL_Rect frames[8][2]) {
  /* Walking Frames */
  frames[0][0] = (SDL_Rect){  0,  0, 64, 64};
  frames[0][1] = (SDL_Rect){ 64,  0, 64, 64};
  
  frames[1][0] = (SDL_Rect){128,  0, 64, 64};
  frames[1][1] = (SDL_Rect){192,  0, 64, 64};
  
  frames[2][0] = (SDL_Rect){256,  0, 64, 64};
  frames[2][1] = (SDL_Rect){320,  0, 64, 64};
  
  frames[3][0] = (SDL_Rect){384,  0, 64, 64};
  frames[3][1] = (SDL_Rect){448,  0, 64, 64};
  
  /* Attacking Frames */
  frames[4][0] = (SDL_Rect){  0, 64, 64, 64};
  frames[4][1] = (SDL_Rect){ 64, 64, 64, 64};
  
  frames[5][0] = (SDL_Rect){128, 64, 64, 64};
  frames[5][1] = (SDL_Rect){192, 64, 64, 64};
  
  frames[6][0] = (SDL_Rect){256, 64, 64, 64};
  frames[6][1] = (SDL_Rect){320, 64, 64, 64};
  
  frames[7][0] = (SDL_Rect){384, 64, 64, 64};
  frames[7][1] = (SDL_Rect){448, 64, 64, 64};
}

void create_dungeon(Entity entities[], int dungeonFloor) {
  Location location = {64, 64};
  Entity player = (Entity){0, IDLE, 10, 0, location, location, true};
  entities[0] = player;

  for (int i = 1; i <= dungeonFloor; i++) {
    location = (Location){i*128, i*128};
    player = (Entity){0, IDLE, 10, 0, location, location, true};
    entities[i] = player;
  }
}

void update_all_entities(Entity entities[], int currentFloor) {
  for (int i=1; i<=currentFloor; i++) {
    /* if an entity is near the player, that entity goes to the player */
    //if (locations_are_nearby(entities[i].location, entities[0].location)) {
    //  entities[i].destination = entities[0].location;
    //  //printf("Dest: (%d, %d)\n", entities[i].destination.x,
    //  //                           entities[i].destination.y);
    //  continue;
    //  // probably not enough time to actually walk
    //  // between being updated
    //}

    /* if it's not, assign an entity a random destination if it has none */
    if (are_same_location(entities[i].location, entities[i].destination)) {
      Location destination = random_destination_from(entities[i].location);
      if (IN_WORLD(destination.x, destination.y)) {
        entities[i].destination = destination;
      }
    }
  }
}

void update_game(unsigned dt, Game *game) {
  if(dt >= 250) {
    update_all_entities(game->entities, game->level);

    game->time = SDL_GetTicks();
    game->frame = game->frame ? 0 : 1;

    if(PLAYER.frames > 0) {
      PLAYER.frames -= 1;

      if(PLAYER.frames == 0) {
        PLAYER.state -= PLAYER.state > 3 ? 4 : 0;
      }
    } else {
      PLAYER.idle = true;
    }
  
    for (int i = 1; i <= game->level; i++) {
      game->entities[i].idle = true;
    }

  }
}

#endif
