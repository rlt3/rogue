#include <time.h>
#include <iostream>
#include <curses.h>
#include "Game.h"

int main()
{
   Game game;

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;

   long next_game_tick = time(NULL);

   int loops;
   char ch;
   bool running=true;

   while(running)
   {
      loops=0;
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP)
      {
         game.moveEntities();
         next_game_tick += SKIP_TICKS;
         loops++;
      }
      if((ch = getch())!=ERR)
      {
         switch (ch)
         {
            case 'j' :
               game.movePlayer(Location (0,1));
               break;
            
            case 'k' :
               game.movePlayer(Location (0,-1));
               break;

            case 'l' :
               game.movePlayer(Location (1,0));
               break;

            case 'h' :
               game.movePlayer(Location (-1,0));
               break;
            
            case 'Q' :
               running=false;
               break;
            
            default:
               break;
         }
      }
   }
   return endwin();
}
