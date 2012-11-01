#include "Render.h"

Render* Render::Render_Instance = NULL;
Animation* Render::Animation_Instance = NULL;

Render::Render()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Dearth", "Dearth");
   this->surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

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
   if(SDL_BlitSurface(sprite, animation, this->surface, location) < 0)
   {
      printf("Error!\n");
   }
}

void Render::update()
{
   //SDL_UpdateRect(this->surface, 0, 0, 0, 0);
}

void Render::quit()
{
	SDL_Quit();
}
