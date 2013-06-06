#ifndef PLAYER_H
#define PLAYER_H
#include <Entity/Entity.h>

class Player : public Entity
{
   public:
      Player() : Entity(PLAYER) { location = Location(50, 50); }
      void move(Location direction)
      {
         location = location + direction;
      }
};
#endif
