#include "Render.h"

Render::Render()
{
   load();
}

Render::~Render()
{
   //quit();
}

void Render::update()
{
   SDL_UpdateRect(this->surface, 0, 0, 0, 0);
}

void Render::drawTile(const char *type, Location location)
{
   /* SDL_Rect Rect = { x, y, w, h }; */
   SDL_Rect spriteLocation = { location.x * SPRITE_SIZE, location.y * SPRITE_SIZE };

   SDL_Surface *sprite = sprites[type];

   drawToSurface(sprite,NULL,&spriteLocation); 
}

void Render::drawEntity(int type, int state, Location location, int frameModifier)
{

   /* When there is a single sprite sheet, the type will change to an Integer and moving
    * along the y-axis will get us our sprite of that entity. So, for a player entity, it
    * would map to 0.
    *
    * #define PLAYER 0, etc...
    */

   int frame_math = ( (SPRITE_SIZE * (2*state)) + SPRITE_SIZE * frameModifier);

   SDL_Rect spriteLocation = { location.x, location.y };
   SDL_Rect frame = { frame_math, type, SPRITE_SIZE, SPRITE_SIZE };

   SDL_Surface *sprite = sprites["sheet"];

   drawToSurface(sprite,&frame,&spriteLocation); 
}

int Render::quit()
{
	SDL_Quit();

   deleteSprite(sprites["sheet"]);
   deleteSprite(sprites["floor"]);

   return 0;
}

void Render::drawToSurface(SDL_Surface *sprite, SDL_Rect *keyframe, SDL_Rect *location)
{
   if(SDL_BlitSurface(sprite, keyframe, this->surface, location) < 0)
      printf("Error!\n");
}

void Render::deleteSprite(SDL_Surface *sprite)
{
   SDL_FreeSurface(sprite);
}

SDL_Surface *Render::loadSprite(const char *filename)
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

void Render::load()
{
   SDL_Init(SDL_INIT_VIDEO);
   SDL_WM_SetCaption("Game", "Game");
   surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

   SDL_EnableKeyRepeat(70, 70);

   colorkey = SDL_MapRGB(surface->format, 255, 0, 255);

   sprites["floor"]   = loadSprite("graphics/floor.png");
   sprites["sheet"]   = loadSprite("graphics/spritesheet.png");
}
