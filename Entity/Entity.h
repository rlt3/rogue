#ifndef ENTITY_H
#define ENTITY_H
#include "../Misc/Typedef.h"
#include "../Misc/Location.h"

class Entity
{
   public:
      Entity(int type);

      void update(int state);
      void idle();
      void move();
      void moveTo(Entity &entity);
      void interpolate();

      bool nearby(Entity &entity);

      int state;
      int speed;
      int type;

      Queue<int> frame;
      
      Location location;
      Location direction;
      Location destination;

   protected:
      Location getDirection();
      static Location randomDestinationFrom(Location now);
      static int getState(Location Direction);
};
#endif
