#ifndef DEARTH_WINDOW_H
#define DEARTH_WINDOW_H

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#define SCREENX           640
#define SCREENY           512
#define TILESIZE          16
#define SPRITESIZE        16

typedef SDL_Surface* Spritesheet;
typedef SDL_Rect     Area;

void window_fill(uint32_t r, uint32_t g, uint32_t b);
void window_draw(Spritesheet sprite, Area *frame, Area *location);
void window_display();

void window_free(Spritesheet *sheet);
void window_load();
void window_quit();

uint32_t get_ticks();

Spritesheet load_sheet(const char *file);

#endif
