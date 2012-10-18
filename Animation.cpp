#include "Animation.h"

Animation::Animation()
{
   this->colorkey = SDL_MapRGB(Render::screen->format, 255, 0, 255);
}

Animation::~Animation()
{
   // foo
}

SDL_Surface *Animation::loadSprite(const char *filename)
{
   //SDL_Surface *sprite;

   //this->temp = SDL_LoadBMP(filename);
	//sprite = SDL_DisplayFormat(this->temp);
	//SDL_FreeSurface(this->temp);

	//SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, this->colorkey);

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

//void animate(SDL_Surface *sprite, SLD_Rect *location, const char *state)
//{
//   /**
//    * Animation State Machine:
//    *    Every frame the Entity will give its state to the state machine.
//    *    The state machine has an instruction set that says to animate
//    *    a particular state. Until the state machine is given new instructions,
//    *    it will animate that particular state:
//    *
//    *    IDLE, IDLE, IDLE, IDLE, etc.
//    *
//    *    Because it is idling, it will simply go back and forth between
//    *    the animations/
//    */
//   SDL_Rect animate;
//
//   animate.x = 128;
//   animate.y = 0;
//   animate.w = SPRITE_SIZE;
//   animate.h = SPRITE_SIZE;
//
//   animate.x += 32;
//
//   Render::draw()
//}

void Animation::deleteSprite(SDL_Surface *sprite)
{
   SDL_FreeSurface(sprite);
}
