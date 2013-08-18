#ifndef DEARTH_RENDER_H
#define DEARTH_RENDER_H

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#define SCREENX           640
#define SCREENY           512

#define TILESIZE          16
#define SPRITESIZE        16

SDL_Surface *load_sprite(const char *file);
SDL_Surface *load_window();

void draw(SDL_Surface *sprite, SDL_Rect *frame, 
          SDL_Surface *screen, SDL_Rect *location);

#endif
