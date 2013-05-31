#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"

class Monster : public Entity
{
   public:
      Monster() : Entity(MONSTER) {}
};
#endif
