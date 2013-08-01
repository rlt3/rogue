#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

#define SCREENX           640
#define SCREENY           512

#define TOTAL_ENTITIES    16
#define PLAYER            game->entities

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < SCREENX && y < SCREENY)


#include <SDL/SDL.h>
#include "Entity.h"

typedef struct Game {
  SDL_Surface    *screen;
  SDL_Surface    *sprites[TOTAL_ENTITIES];
  SDL_Rect       frames[8][2];
  Entity         entities;

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

void create_dungeon(Game *game, int dungeonFloor) {
  /* Player is always at the start of the list */
  game->entities = (Entity){
    .type        = 0, 
    .state       = IDLE, 
    .hp          = 10,
    .frames      = 0, 
    .location    = ((Location){64, 64}),
    .destination = ((Location){64, 64}),
    .idle        = true,
    .next        = NULL
  };

  Entity *previous = &game->entities;
  for (int i = 1; i <= dungeonFloor; i++ ) { 
    previous->next = malloc(sizeof(*previous->next));

    if (previous->next == NULL) {
      puts("Out of Memory: can't create more monsters\n");
      exit(1);
    }   

    *previous->next = (Entity){
      .type        = 0, 
      .state       = IDLE, 
      .hp          = 10,
      .frames      = 0, 
      .location    = ((Location){i*128, i*128}),
      .destination = ((Location){i*128, i*128}),
      .idle        = true,
      .next        = NULL
    };

    previous = previous->next;
  }   
}

void update_all_entities(Entity *start, int currentFloor) {
  Entity *entity = start->next;
  while (entity != NULL) {

  /* if it's not, assign an entity a random destination if it has none */
    if (are_same_location(entity->location, entity->destination)) {
      Location destination = random_destination_from(entity->location);
      if (IN_WORLD(destination.x, destination.y)) {
        entity->destination = destination;
      }
    }
    entity = entity->next;
  }

  //for (int i=1; i<=currentFloor; i++) {

  //  /* if an entity is near the player, that entity goes to the player */
  //  if (locations_are_nearby(entities[i].location, entities[0].location)) {
  //    entities[i].destination = entities[0].location;
  //    continue;
  //  }
}

/* 
 * For every .25 seconds (quarter second) update the 
 * global frame and keep track of each entity's 
 * special animation frames.
 */
void update_game(unsigned dt, Game *game) {
  if(dt >= 250) {
    update_all_entities(&game->entities, game->level);

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

    /* Don't update the player */
    Entity *entity = game->entities.next;
    while (entity != NULL) {
      entity->idle = true;
      entity = entity->next;
    }
  }
}

#endif
