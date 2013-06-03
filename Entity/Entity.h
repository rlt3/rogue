#ifndef ENTITY_H
#define ENTITY_H
#include "../Misc/Typedef.h"
#include "../Misc/Location.h"

class Entity
{
   public:
      Entity(int type);
      void nextFrame();
      void update(int state);
      void move();
      void moveTowards(Location destination);
      void interpolate();

      int state;
      int speed;
      int type;
      
      Location location;
      Location direction;
      Location destination;

      int axis; // x == 0, y == 1

      Queue<int> frame;

      Location getDirection();
      static Location randomDirection();
      static int getState(Location Direction);
   protected:
};
#endif
