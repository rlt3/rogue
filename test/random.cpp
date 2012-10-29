#include <time.h>
#include <iostream>

int main()
{
   srand( time(NULL) ); //Randomize seed initialization
   int num = rand() % 3; // three values: -1,0,1

   int zor = num^1;
   int notzor = ~zor;

   printf("Random number: %d\n", num);
   printf("    ZOR: %d\n", zor);
   printf("   ~ZOR: %d\n", notzor);
   printf(" ~ZOR|1: %d\n", notzor|1);
   printf(" ~ZOR&1: %d\n", notzor&1);
   printf("  Shift: %d\n", num>>1);
   return 0; 
}
