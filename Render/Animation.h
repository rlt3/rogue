#ifndef ANIMATION_H
#define ANIMATION_H
#include <map>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "Render.h"
#include "../Entity/Entity.h"
#include "Queue.h"

typedef Queue<SDL_Rect> animationQueue;

/**
 * This is the Animation State Machine. Each entity holds a particular
 * state (WALK_LEFT, IDLE, ...) and a type (skeleton, player, ...).
 *
 * When the Animation State Machine is instatiated, it loads all of the
 * sprites of the game, rather than each entity hold its own sprite.
 *
 * When the sprites get drawn each frame, they just pass along their
 * type, location, and state and the State Machine filters this 
 * information and passes the propriety objects like SDL_Surface
 * to the Rendering machine itself.
 *
 * The Animation State Machine is simply a filter.
 *
 * This Animation State Machine also uses the singleton method;
 */

class Animation
{
   public:
      static Animation *instance();
      void draw(const char *type, Location location, const char* state);
   protected:
      SDL_Surface *loadSprite(const char *filename);
      void deleteSprite(SDL_Surface *sprite);
      static std::map<const char*, SDL_Surface*> sprites;
      static std::map<const char*, animationQueue> keyframes;
      SDL_Surface *temp;
      int colorkey;
   private:
      Animation();
      static Animation *object;
};
#endif
