#include <time.h>
#include "Render.h"
#include "Animation.h"

int main(int argc, char* argv[]) {
   Render::init();
   Animation animation;

   SDL_Surface *player, *floor;
   SDL_Rect animate, location, floorLocation;

   player = animation.loadSprite("player.bmp");
   floor = animation.loadSprite("floor.bmp");

   location.x = 250;
   location.y = 250;

   animate.x = 128;
   animate.y = 0;
   animate.w = SPRITE_SIZE;
   animate.h = SPRITE_SIZE;

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;
   long next_game_tick = time(NULL);
   int loops;

   bool running = true;
   while(running) {
      SDL_Event event;
      loops=0;

      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP) {
         next_game_tick += SKIP_TICKS;
         loops++;
      }

      while(SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_KEYDOWN:
               switch(event.key.keysym.sym) {
                  case SDLK_ESCAPE:
                  case SDL_QUIT:
                    running=false;
                    break;
               }
            break;
         }
      }

		for (int x = 0; x < SCREEN_WIDTH / SPRITE_SIZE; x++) {
			for (int y = 0; y < SCREEN_HEIGHT / SPRITE_SIZE; y++) {
				floorLocation.x = x * SPRITE_SIZE;
				floorLocation.y = y * SPRITE_SIZE;
            Render::draw(floor, NULL, &floorLocation);
			}
		}

      Render::draw(player, &animate, &location);

      Render::game();
   }
   Render::quit();
   return 0;
}
