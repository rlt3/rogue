#include "Render.h"

Render* Render::Render_Instance = NULL;
Animation* Render::Animation_Instance = NULL;

Render::Render()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Dearth", "Dearth");
   Render::screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	SDL_EnableKeyRepeat(70, 70);
}

Render* Render::screen()
{
   if(!Render::Render_Instance)
      Render::Render_Instance = new Render();
   return Render_Instance;
}

Animation* Render::animation()
{
   return Animation::instance();
}

void Render::draw(SDL_Surface *sprite, SDL_Rect *animation, SDL_Rect *location)
{
   SDL_BlitSurface(sprite, animation, this->surface, location);
}

void Render::updateScreen()
{
   SDL_UpdateRect(Render::screen, 0, 0, 0, 0);
}

void Render::quit()
{
	SDL_Quit();
}
