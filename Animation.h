#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL/SDL.h>
#include "Render.h"

class Animation
{
   public:
      Animation();
      ~Animation();
      SDL_Surface *loadSprite(const char *filename);
      void deleteSprite(SDL_Surface *sprite);
   private:
      SDL_Surface *temp;
      int colorkey;
};
#endif
