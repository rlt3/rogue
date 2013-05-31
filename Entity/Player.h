#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
   public:
      Player() : Entity(PLAYER) {}
      void move(Location direction)
      {
         location = location + direction;
      }
};
#endif
