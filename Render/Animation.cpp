#include "Animation.h"

std::map<const char*, SDL_Surface*> Animation::sprites;

Animation* Animation::instance = NULL;

Animation::Animation()
{
   this->colorkey = SDL_MapRGB(Render::screen->format, 255, 0, 255);

   Animation::sprites["Player"] = this->loadSprite("graphics/player.png");
   Animation::sprites["Monster"] = this->loadSprite("graphics/monster.png");
}

Animation* Animation::instance()
{
   if(!Animation::instance)
      Animation::instance  = new Animation();
   return Animation::instance;
}

void animate(const char *type, Location location, SDL_Rect animation);
{
   /**
    * Animation State Machine:
    *    Every frame the Entity will give its state to the state machine.
    *    The state machine has an instruction set that says to animate
    *    a particular state. Until the state machine is given new instructions,
    *    it will animate that particular state:
    *
    *    IDLE, IDLE, IDLE, IDLE, etc.
    *
    *    Because it is idling, it will simply go back and forth between
    *    the animations/
    */
}

SDL_Surface *Animation::loadSprite(const char *filename)
{
   SDL_Surface *temp = IMG_Load(filename);
   SDL_Surface *sprite;

   if (temp == NULL)
   {
      printf("Failed to load image %s\n", filename);
      exit(1);
   }

   SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));
   sprite = SDL_DisplayFormat(temp);
   SDL_FreeSurface(temp);

   if (sprite == NULL)
   {
      printf("Failed to convert image to native format %s\n", filename);
      exit(1);
   }

   return sprite;
}

void Animation::deleteSprite(SDL_Surface *sprite)
{
   SDL_FreeSurface(sprite);
}
