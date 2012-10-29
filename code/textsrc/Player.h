#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
   public:
      Player()
      {
         this->health = 10;
         this->level  = 1;
         this->floor  = 1;
         this->location = Location (1,1);
         this->previous = this->location;
      }
};
#endif
