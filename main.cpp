#include "Game.h"

int main(int argc, char* argv[])
{
   Game* game = new Game();

   SDL_Event event;

   int keypress = 0;
   int h=0; 

   while(!keypress) 
   {
      game->draw();
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
                    keypress = 1;
                    break;
                  case SDL_QUIT:
                    keypress = 1;
                    break;
               }
               break;
         }
      }
   }
   SDL_Quit();
   return 0;
}
