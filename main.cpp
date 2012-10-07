#include <time.h>
#include <curses.h>
#include "typedef.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "Monster.h"

int main()
{
   keypad(initscr(),1);
   curs_set(0);
   start_color(); 
   nodelay(stdscr, TRUE);

   char ch;
   int floor;

   Map map;
   Player player;
   
   Monster* gob1 = new Monster(Location (4, 12));
   Monster* gob2 = new Monster(Location (4, 13));
   Monster* gob3 = new Monster(Location (4, 14));

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;

   long next_game_tick = time(NULL);

   int loops;

   bool playerInput=true;
   bool running=true;
   map.draw(); //map.draw(floor);
   player.draw();
   mvaddch(MAP_HEIGHT+2,0,32);
   while(running)
   {
      loops=0;
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP)
      {
         floor = player.floor;
         gob1->draw();
         gob2->draw();
         gob3->draw();
         mvaddch(MAP_HEIGHT+2,0,32);

         gob1->move(Location (1,0));
         gob2->move(Location (1,0));
         gob3->move(Location (1,0));

         next_game_tick += SKIP_TICKS;
         loops++;
      }
      //while(playerInput)
      //{
      //   player.draw();
      //   mvaddch(MAP_HEIGHT+2,0,32);
      //   playerInput=false;
      //}
      if((ch = getch())!=ERR)
      {
         switch (ch)
         {
            case 'j' :
               player.move(Location (0,1));
               player.draw();
               mvaddch(MAP_HEIGHT+2,0,32);
               //playerInput=true;
               //next_game_tick -= SKIP_TICKS;
               break;
            
            case 'k' :
               player.move(Location (0,-1));
               player.draw();
               mvaddch(MAP_HEIGHT+2,0,32);
               //playerInput=true;
               //next_game_tick -= SKIP_TICKS;
               break;

            case 'l' :
               player.move(Location (1,0));
               player.draw();
               mvaddch(MAP_HEIGHT+2,0,32);
               //playerInput=true;
               //next_game_tick -= SKIP_TICKS;
               break;

            case 'h' :
               player.move(Location (-1,0));
               player.draw();
               mvaddch(MAP_HEIGHT+2,0,32);
               //playerInput=true;
               //next_game_tick -= SKIP_TICKS;
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
