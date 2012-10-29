#include "Animation.h"

class Dungeon
{
   public:
      Dungeon();
      void draw();
      void updateEntities();
      void generate();
   protected:
      SDL_Surface *sprite;
};
