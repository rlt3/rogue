#include <SDL/SDL.h>
//#include <SDL_image/SDL_image.h>

class Render
{
   public:
      // Initialize SDL
      Render();
      // SDL_Quit -- Make sure to SDL_FreeSurface on sprites
      ~Render();

      // SDL_Blit the sprite, animation, and position to screen
      void draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location);

      // render the screen
      void game();
   private:
      SDL_Surface *screen;
}
