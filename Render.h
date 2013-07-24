#ifndef ROGUE_RENDER_H
#define ROGUE_RENDER_H

#define SCREENX           640
#define SCREENY           512

#define TILESIZE          32
#define SPRITESIZE        64

#define FLOOR             0
#define ENTITY            1

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "Entity.h"

SDL_Surface *load_window();

void load_animations(SDL_Surface *sprites[], SDL_Rect frames[8][2]);

SDL_Surface *load_sprite(const char filename[]);

void render(SDL_Surface *screen, Entity *entities, 
            SDL_Surface *sprites[], SDL_Rect frames[8][2],
            int frameToDraw);

void draw_tile(SDL_Surface *screen, SDL_Surface *sprites[], 
             uint8_t type, uint32_t x, uint32_t y);

void draw_entity(SDL_Surface *screen, Entity *entity, 
                 SDL_Surface *sprites[], SDL_Rect frames[8][2], 
                 int frameToDraw);

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location);


SDL_Surface * load_window() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  atexit(SDL_Quit);

  return SDL_GetVideoSurface();
}

void load_animations(SDL_Surface *sprites[], SDL_Rect frames[8][2]) {
  sprites[FLOOR]  = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 

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

SDL_Surface *load_sprite(const char filename[]) {
  SDL_Surface *temp = IMG_Load(filename);

  SDL_SetColorKey(temp, 
      (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
      SDL_MapRGB(temp->format, 0, 0, 0));

  if (temp == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Surface *sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  if (sprite == NULL) {
    printf("Failed to convert image to native format %s\n", filename);
    exit(1);
  }

  return sprite;
}

void render(SDL_Surface *screen, Entity *entities, 
            SDL_Surface *sprites[], SDL_Rect frames[8][2],
            int frameToDraw) {
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(screen, sprites, FLOOR, x, y);
    }
  }

  draw_entity(screen, &entities[0], sprites, frames, frameToDraw);
  SDL_Flip(screen);
}

void draw_tile(SDL_Surface *screen, SDL_Surface *sprites[], 
             uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location     = {x * TILESIZE, y * TILESIZE};
  SDL_Surface *sprite   = sprites[type];

  draw(sprite, NULL, screen, &location);
}

void draw_entity(SDL_Surface *screen, Entity *entity, 
                 SDL_Surface *sprites[], SDL_Rect frames[8][2], 
                 int frameToDraw) {
  int animation_frame   = entity->idle? 0 : frameToDraw;
  SDL_Rect location     = {entity->location.x, entity->location.y};
  SDL_Surface *sprite   = sprites[ENTITY];
  SDL_Rect frame        = frames[entity->state][animation_frame];

  draw(sprite, &frame, screen, &location); 
}

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location) {
  if(SDL_BlitSurface(sprite, frame, screen, location) < 0) {
    printf("Error! Drawing Entity: %s\n", SDL_GetError());
  }
}

#endif
