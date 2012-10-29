#include <cstdio>
#include <ctime>
#include <time.h>
using namespace std;

int pause(int x)
{
   long T1,T3,T2;
   T1=time(&T2);
   T3=(time(&T2)) + x;
   while(time(&T2) < T3);
   return(x);
}

int main()
{
   clock_t start = clock();
   /* Code you want timed here */

   const int TICKS_PER_SECOND = 60;
   const int SKIP_TICKS = 80 / TICKS_PER_SECOND;
   const int MAX_FRAMESKIP = 10;

   long next_game_tick = time(NULL);

   int loops;

   while(1)
   {
      loops=0;
      while(time(NULL) > next_game_tick && loops < MAX_FRAMESKIP)
      {
         next_game_tick += SKIP_TICKS;
         printf("Number of loops: %d\n", loops);
         loops++;
      }
   }

   printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
   printf("Number of loops: %d\n", loops);
   return 0;
   //time_t t2, t1 = time(NULL); 
   //int count=0;
   //while(1)
   //{
   //   time_t t2 = time(NULL);
   //   while(difftime(t2, t1) = 0.30)
   //   {
   //     //DO the stuff!
   //     printf("Count: %d\n", count);
   //     count++;
   //     t1 = time(NULL);
   //   }
   //   //if(difftime(t2, t1) > 0.30)
   //   //{
   //   //  //DO the stuff!
   //   //  printf("Count: %d\n", count);
   //   //  count++;
   //   //  t1 = time(NULL);
   //   //}
   //}
}
