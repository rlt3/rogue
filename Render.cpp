#include "Render.h"

SDL_Surface *Render::screen;

void Render::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Dearth", "Dearth");
   Render::screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	SDL_EnableKeyRepeat(70, 70);
}

void Render::quit()
{
	SDL_Quit();
}

void Render::draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location)
{
   SDL_BlitSurface(sprite, animation, Render::screen, location);
}

void Render::game()
{
   SDL_UpdateRect(Render::screen, 0, 0, 0, 0);
}
