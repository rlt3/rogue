#include <time.h>
#include "Render.h"
#include "Animation.h"
#include "Player.h"

int main(int argc, char* argv[]) {
   Render::init();
   Animation animation;
   Player player;

   SDL_Surface *floor;
   SDL_Rect floorLocation;

   floor = animation.loadSprite("floor.bmp");

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
         player.update(NULL);
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
                  case SDLK_a:
                     player.update("WALK_LEFT");
                     break;
                  case SDLK_d:
                     player.update("WALK_RIGHT");
                     break;
                  case SDLK_w:
                     player.update("WALK_UP");
                     break;
                  case SDLK_s:
                     player.update("WALK_DOWN");
                     break;
                  case SDLK_1:
                     //player.update("ATTACK");
                     break;
               }
               break;
            case SDL_KEYUP:
               player.update("IDLE");
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
      player.draw();
      Render::game();
   }
   Render::quit();
   return 0;
}
