#include "Render.h"

Render::Render()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Dearth", "Dearth");
	this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	SDL_EnableKeyRepeat(70, 70);
}

~Render::Render()
{
	SDL_Quit();
}

void draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location)
{
   SDL_BlitSurface(sprite, animation, this->screen, location);
}

void game()
{
   SDL_UpdateRect(this->screen, 0, 0, 0, 0);
}
