#ifndef ROGUE_HEART_HPP
#define ROGUE_HEART_HPP

#include "Item.hpp"

class Heart : public Item {
public:
  Heart(Location location) : Item(TYPE_HEART, location){
    this->type = TYPE_HEART;
    this->location = location;
  }

  void apply_effect(Entity *entity) 
    { entity->hp += 2; }
};

#endif
