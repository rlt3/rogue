#include <time.h>
#include "Game.h"

int main(int argc, char* argv[])
{
   Game* game = new Game();

   SDL_Event event;

   int loops;
   bool running=true;

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;

   long next_game_tick = time(NULL);

   while(running)
   {
      game->draw();
      loops=0;
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP)
      {
         // only update entities and mechanics in here
         // probably not a good idea to redraw the screen all the time
         // but I dunno
         game->updateEntities();
         next_game_tick += SKIP_TICKS;
         loops++;
      }
      while(SDL_PollEvent(&event)) 
      {      
         switch (event.type) 
         {
            case SDL_KEYDOWN:
               switch(event.key.keysym.sym)
               {
                  case SDLK_j:
                     game->movePlayer(Location (0,1));
                     break;
                  case SDLK_k:
                     game->movePlayer(Location (0,-1));
                     break;
                  case SDLK_l:
                     game->movePlayer(Location (1,0));
                     break;
                  case SDLK_h:
                     game->movePlayer(Location (-1,0));
                     break;
                  case SDLK_ESCAPE:
                    running=false;
                    break;
                  case SDL_QUIT:
                    running=false;
                    break;
               }
               break;
         }
      }
   }
   SDL_Quit();
   return 0;
}
