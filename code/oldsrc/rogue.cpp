#include <curses.h>
#include "map.h"
#include "monster.h"
#include "player.h"
using namespace std;

int main()
{
   // initialize curses
   keypad(initscr(),1);
   curs_set(0);
   start_color(); 

   char input;
   int floor;

   // create a Map and Player object
   Map map;
   Player player;

   bool game=true;
   while(game)
   {
      if(player.getFloor() != floor)
      {
         floor = player.getFloor();
         Monster::generate(floor);
      }

      // draw the Map and Player object
      Monster::draw();
      map.draw();   
      player.lifebar();
      player.draw();

      if(player.getHealth()<=0)
      {
         const char str[] = "You have lost!";
         for (int y=1;y<=MAP_HEIGHT;y++)
            for (int x=1;x<=MAP_WIDTH;x++)
               mvaddch(y,x,32);
         for (int y=1;y<=MAP_HEIGHT;y++)
            for (int x=1;x<=MAP_WIDTH;x++)
               mvaddstr(10,5,str);
         getch();
         return endwin();
      }

      // wait for key press before continuing
      input = getch();

      // then process the key press
      switch (input)
      {
         /*
          * I use vi input commands because hjkl 
          * are the best for up/down, left/right
          * movement.
          */

         // Move Down
         case 'j' :
            player.move(2);
            break;
         
         // Move Up
         case 'k' :
            player.move(0);
            break;

         // Move Right
         case 'l' :
            player.move(1);
            break;

         // Move Left
         case 'h' :
            player.move(3);
            break;
         
         // Quit
         case 'Q' :
            game=false;
            break;
         
         default:
            break;
      }
   }
   // free the terminal from forced slavery
   return endwin();
}
