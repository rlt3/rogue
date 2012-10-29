#include "Queue.h"

struct animation_dimensions
{
   int x;
   int y;
   int w;
   int h;
}

typedef Queue<animation_dimensions> Animation;
