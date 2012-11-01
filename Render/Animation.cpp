#include "Animation.h"

Animation* Animation::object = NULL;
std::map<const char*, SDL_Surface*> Animation::sprites;
std::map<const char*, animationQueue> Animation::keyframes;

Animation::Animation()
{
   this->colorkey = SDL_MapRGB(Render::screen()->surface->format, 255, 0, 255);

   /**
    * Loading each of the sprites to an associative array so each Entity
    * does not have a sprite in memory.
    */

   Animation::sprites["player"]  = this->loadSprite("graphics/player.png");
   Animation::sprites["monster"] = this->loadSprite("graphics/monster.png");
   Animation::sprites["floor"]   = this->loadSprite("graphics/floor.png");

   /**
    * Make a queue that alternates between frames, which are written
    * onto the screen.
    *
    * Each queue is associative to a certain state. So, the IDLE
    * state has two frames, which show the Entity idling. The
    * WALK_RIGHT has two frames showing an Entity walking right.
    *
    * These frames simply correspond with the pixels on the
    * sprite sheet.
    */

   SDL_Rect frame;
   frame.w = SPRITE_SIZE; frame.h = SPRITE_SIZE;
   animationQueue idle, w_left, w_right, w_up, w_down; 

   frame.y=0; frame.x=256; idle.push(&frame);
   frame.y=0; frame.x=320; idle.push(&frame);

   frame.y=0; frame.x=384; w_left.push(&frame);
   frame.y=0; frame.x=448; w_left.push(&frame);

   frame.y=0; frame.x=128; w_right.push(&frame);
   frame.y=0; frame.x=192; w_right.push(&frame);

   frame.y=0; frame.x=0;   w_up.push(&frame);
   frame.y=0; frame.x=64;  w_up.push(&frame);

   frame.y=0; frame.x=256; w_down.push(&frame);
   frame.y=0; frame.x=320; w_down.push(&frame);

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

void Animation::draw(const char *type, Location location, const char *state)
{
   /**
    * Do all the necessary conversions for the specific proprietary
    * calls that need to be made.
    *
    * We convert the location pair into a SDL_Rect and use the state
    * to look up a frame from the assosciative state array.
    *
    * The same goes for picking out the sprite.
    */
   if(type=="player")
   {
      printf("drawing player...\n");
      SDL_Rect spriteLocation;
      spriteLocation.x = location.first;
      spriteLocation.y = location.second;

      SDL_Rect frame;
      frame.w = SPRITE_SIZE; frame.h = SPRITE_SIZE;
      frame.y=0; frame.x=256;

      SDL_Surface *sprite = Animation::sprites[type];

      Render::screen()->draw(sprite,&frame,&spriteLocation); 
   }
   else
   {
      // SDL_Rect for the Sprite's location
      SDL_Rect spriteLocation;
      spriteLocation.x = location.first*SPRITE_SIZE;
      spriteLocation.y = location.second*SPRITE_SIZE;

      // SDL_Rect for the specific animation frame
      SDL_Rect *frame = (state==NULL) ? NULL : Animation::keyframes[state].next();

      // Get the sprite based on the type received
      SDL_Surface *sprite = Animation::sprites[type];

      Render::screen()->draw(sprite,frame,&spriteLocation); 
   }
}

SDL_Surface *Animation::loadSprite(const char *filename)
{
   SDL_Surface *temp = IMG_Load(filename);
   SDL_Surface *sprite;

   if (temp == NULL)
   {
      printf("Error: %s\n", IMG_GetError());
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
