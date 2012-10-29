#ifndef RENDER_H
#define RENDER_H
#include <SDL/SDL.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 512
#define SPRITE_SIZE    64

class Render
{
   public:
      SDL_Surface static *screen;

      // Initialize SDL
      void static init();

      // SDL_Quit
      void static quit();

      // SDL_Blit the sprite, animation, and position to screen
      void static draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location);

      // render the screen
      void static game();
};
#endif
