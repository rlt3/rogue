#ifndef RENDER_H
#define RENDER_H
#include <SDL/SDL.h>
#include "Animation.h"

class Animation;

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 512
#define SPRITE_SIZE    64

/**
 * Using the Singleton Method, we ensure that Render does not
 * get instantiated multiple times and can hold its own state.
 *
 * It can be globally called like this:
 *
 * Render::screen()->update();
 *
 * For something looking to animate an Entity, that call would look
 * like this:
 *
 * Render::animation()->draw(this->type, this->location, this->state);
 */

class Render 
{
   public:
      static Render *screen();
      static Animation *animation();
      SDL_Surface *surface;
      void draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location);
      void update();
      void quit();
   private:
      Render();
      static Render *Render_Instance;
      static Animation *Animation_Instance;
};
#endif
