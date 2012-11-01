#include <time.h>
#include "Game.h"
#include "Entity/Entity.h"

int main(int argc, char* argv[]) {
   Game game;

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;
   long next_game_tick = time(NULL);
   int loops;

   game.update();

   bool running = true;
   while(running) {
      SDL_Event event;
      loops=0;

      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP) {
         /**
          * Update the Dungeon Entities
          */
         game.update();
         next_game_tick += SKIP_TICKS;
         loops++;
      }

      while(SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_KEYDOWN:
               switch(event.key.keysym.sym) {
                  case SDLK_ESCAPE: case SDL_QUIT:
                    running=false;
                    break;
                  case SDLK_w: case SDLK_UP: case SDLK_k:
                     game.updatePlayer("WALK_UP");
                     break;
                  case SDLK_a: case SDLK_LEFT: case SDLK_h:
                     game.updatePlayer("WALK_LEFT");
                     break;
                  case SDLK_s: case SDLK_DOWN: case SDLK_j:
                     game.updatePlayer("WALK_DOWN");
                     break;
                  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
                     game.updatePlayer("WALK_RIGHT");
                     break;
                  case SDLK_1:
                     //player.update("ATTACK");
                     break;
               }
               break;
            case SDL_KEYUP:
               game.updatePlayer("IDLE");
               break;
         }
      }

      game.display();
   }

   Render::screen()->quit();
   return 0;
}
