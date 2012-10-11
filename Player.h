#include "Animation.h"
#include "Render.h"

class Player
{
   public:
      Player();
      void draw();
      void update(const char *state);
   protected:
      SDL_Surface *sprite;
      SDL_Rect animate, location; 
      const char *state;
      int count;
};
