#ifndef RENDER_H
#define RENDER_H
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <map>

#include <Misc/Typedef.h>
#include <Misc/Location.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 512
#define SPRITE_SIZE    64

class Render
{
   public:
      Render();
      ~Render();
      void update();
      void drawTile(const char *type, Location location);
      void drawEntity(int type, int state, Location location, int frame);
      //void display();
      int quit();

   protected:
      void drawToSurface(SDL_Surface *sprite, SDL_Rect *keyframe, SDL_Rect *location);
      void deleteSprite(SDL_Surface *sprite);

      SDL_Surface *loadSprite(const char *filename);
      SDL_Surface *surface;

      std::map<const char*, SDL_Surface*> sprites;
      std::map<const char*, animationQueue> keyframes;

      int colorkey;

   private:
      void load();
      int count;
};

#endif
