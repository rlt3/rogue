#ifndef ENTITY_H
#define ENTITY_H
#include "../Graphics/Animation.h"

class Entity
{
   public:
      Entity();
      void draw();
      void update(const char *state);
   protected:
      // probably need map or something so Entities can 'choose'
      // which sprite to use based on their type: Goblins use
      // the goblin sprite, etc.
      SDL_Surface *sprite;
      Animation animation;
      const char *state;
};
#endif
