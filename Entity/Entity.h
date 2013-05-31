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
      void interpolate();

      int state;
      int speed;
      int type;
      
      Location location;
      Location direction;
      Location destination;
      Location grid;

      Queue<int> frame;

   protected:
      Location randomDirection();
      int getState(Location Direction);
};
#endif
