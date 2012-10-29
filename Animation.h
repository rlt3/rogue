#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "Render.h"

class Animation
{
   public:
      Animation();
      ~Animation();
      SDL_Surface *loadSprite(const char *filename);
      //void animate(SDL_Surface *sprite, const char *state);
      void deleteSprite(SDL_Surface *sprite);
   private:
      SDL_Surface *temp;
      int colorkey;
};
#endif
