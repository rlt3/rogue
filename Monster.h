#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"

class Monster : public Entity
{
   public:
      Monster(Location location)
      {
         this->health = 10;
         this->level  = 1;
         this->floor  = 1;
         this->location  = location;
         this->previous = this->location;
      }
      void move(Location destination)
      {
         this->location.first += destination.first;
         this->location.second += destination.second;
         //this->location.second += -1;
      }
};
#endif
