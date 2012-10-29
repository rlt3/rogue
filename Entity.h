#ifndef ENTITY_H
#define ENTITY_H
#include "Animation.h"
#include "Render.h"

class Entity
{
   public:
      Entity();
      void draw();
      void update(const char *state);
   protected:
      SDL_Surface *sprite;
      SDL_Rect animate, location; 
      const char *state;
      int count;
};
#endif
