#ifndef ROGUE_SCREEN_HPP
#define ROGUE_SCREEN_HPP

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

class Screen {
public:
  Screen();

protected:
  static SDL_Surface *surface;
  static SDL_Surface *load_sprite(const char* file);
  static SDL_Surface *load_window();

  void draw(SDL_Surface *sprite, SDL_Rect *frame, 
            SDL_Surface *screen, SDL_Rect *location);
};

#endif
