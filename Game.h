#ifndef ROGUE_GAME_H
#define ROGUE_GAME_H

#define SCREENX           640
#define SCREENY           512

#define TOTAL_ENTITIES    16
#define PLAYER            game->entities[0]

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

SDL_Surface *load_window();
void load_frames(SDL_Rect frames[8][2]);

SDL_Surface * load_window() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  atexit(SDL_Quit);

  return SDL_GetVideoSurface();
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

#endif
