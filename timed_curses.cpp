#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <curses.h>
#include "Map.h"
#include "Player.h"

int main()
{
   struct termios oldSettings, newSettings;

   tcgetattr( fileno( stdin ), &oldSettings );
   newSettings = oldSettings;
   newSettings.c_lflag &= (~ICANON & ~ECHO);
   tcsetattr( fileno( stdin ), TCSANOW, &newSettings );

   keypad(initscr(),1);
   curs_set(0);
   start_color(); 

   char c;
   int floor;

   Map map;
   Player player;

   bool game=true;
   while(game)
   {
      fd_set set;
      struct timeval tv;

      tv.tv_sec = 1;
      tv.tv_usec = 0;

      FD_ZERO( &set );
      FD_SET( fileno( stdin ), &set );

      int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

      floor = player.floor;
      map.draw(); //map.draw(floor);
      player.draw();

      if(res>0)
      {
         read( fileno( stdin ), &c, 1 );
         switch (c)
         {
            case 'j' :
               player.move(Location (0,1));
               break;
            
            case 'k' :
               player.move(Location (0,-1));
               break;

            case 'l' :
               player.move(Location (1,0));
               break;

            case 'h' :
               player.move(Location (-1,0));
               break;
            
            case 'Q' :
               game=false;
               break;
            
            default:
               break;
         }
      }
   }
   tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
      return endwin();
}
