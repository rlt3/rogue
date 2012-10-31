#include "Animation.h"

Animation* Animation::object = NULL;
std::map<const char*, SDL_Surface*> Animation::sprites;
std::map<const char*, animationQueue> Animation::keyframes;

Animation::Animation()
{
   this->colorkey = SDL_MapRGB(Render::screen()->surface->format, 255, 0, 255);

   Animation::sprites["player"] = this->loadSprite("graphics/player.png");
   Animation::sprites["monster"] = this->loadSprite("graphics/monster.png");

   SDL_Rect frame;
   animationQueue idle, w_left, w_right, w_up, w_down; 

   frame.y=0; frame.x=256; idle.push(frame);
   frame.y=0; frame.x=320; idle.push(frame);

   frame.y=0; frame.x=384; w_left.push(frame);
   frame.y=0; frame.x=448; w_left.push(frame);

   frame.y=0; frame.x=128; w_right.push(frame);
   frame.y=0; frame.x=192; w_right.push(frame);

   frame.y=0; frame.x=0;   w_up.push(frame);
   frame.y=0; frame.x=64;  w_up.push(frame);

   frame.y=0; frame.x=256; w_down.push(frame);
   frame.y=0; frame.x=320; w_down.push(frame);

   Animation::keyframes["IDLE"] = idle;
   Animation::keyframes["WALK_LEFT"] = w_left;
   Animation::keyframes["WALK_RIGHT"] = w_right;
   Animation::keyframes["WALK_UP"] = w_up;
   Animation::keyframes["WALK_DOWN"] = w_down;
}

Animation* Animation::instance()
{
   if(!Animation::object)
      Animation::object  = new Animation();
   return Animation::object;
}

void animate(const char *type, Location location, SDL_Rect animation)
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
