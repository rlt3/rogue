#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main()
{
   struct termios oldSettings, newSettings;

   tcgetattr( fileno( stdin ), &oldSettings );
   newSettings = oldSettings;
   newSettings.c_lflag &= (~ICANON & ~ECHO);
   tcsetattr( fileno( stdin ), TCSANOW, &newSettings );

   int count=0;

   for(;;)
   {
      fd_set set;
      struct timeval tv;

      tv.tv_sec = 1;
      tv.tv_usec = 0;

      FD_ZERO( &set );
      FD_SET( fileno( stdin ), &set );

      int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

      printf("Count: %d\n", count);
      count++;

      if( res > 0 )
      {
         char c;
         printf( "Input available: " );
         read( fileno( stdin ), &c, 1 );
         switch(c)
         {
            case 'Q':
               tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
               return 0;
               break;
            default:
               printf( "%c\n", c);
               break;
         }
      }
      else
      {
         //printf( "Select timeout\n" );
      }
   }
   tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
      return 0;
}
