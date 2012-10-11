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
   SDL_Surface *sprite;

   this->temp = SDL_LoadBMP(filename);
	sprite = SDL_DisplayFormat(this->temp);
	SDL_FreeSurface(this->temp);

	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, this->colorkey);

   return sprite;
}

void Animation::deleteSprite(SDL_Surface *sprite)
{
	SDL_FreeSurface(sprite);
}
