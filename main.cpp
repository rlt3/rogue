#include <iostream>
#include <time.h>
#include "Game.h"
#include "Entity/Entity.h"

int main(int argc, char* argv[]) {
   Game game;

   //const int TICKS_PER_SECOND = 17;
   //const int SKIP_TICKS = 100 * TICKS_PER_SECOND;
   //const int MAX_FRAMESKIP = 10;
   //clock_t next_game_tick = clock();

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;
   long next_game_tick = time(NULL);
   int loops;

   //game.display();
   game.update();

   bool running = true;
   while(running) {
      SDL_Event event;
      loops=0;

      //while(clock() > next_game_tick && loops < MAX_FRAMESKIP) {
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP) {
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
                     game.updatePlayer("WALK_UP", std::make_pair(0,-10));
                     break;
                  case SDLK_a: case SDLK_LEFT: case SDLK_h:
                     game.updatePlayer("WALK_LEFT", std::make_pair(-10,0));
                     break;
                  case SDLK_s: case SDLK_DOWN: case SDLK_j:
                     game.updatePlayer("WALK_DOWN", std::make_pair(0,10));
                     break;
                  case SDLK_d: case SDLK_RIGHT: case SDLK_l:
                     game.updatePlayer("WALK_RIGHT", std::make_pair(10,0));
                     break;
                  case SDLK_1:
                     //player.update("ATTACK");
                     break;
               }
               break;
            case SDL_KEYUP:
               //game.updatePlayer("IDLE", std::make_pair(0,0));
               break;
         }
      }
      game.display();
   }
   Render::screen()->quit();
   return 0;
}
