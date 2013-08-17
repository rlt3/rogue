#ifndef ROGUE_ITEM_HPP
#define ROGUE_ITEM_HPP

#define TYPE_HEART    240

#include <stdint.h>

#include "Entity.hpp"
#include "Location.hpp"

class Item;

typedef std::list<Item *>::iterator Item_Iterator;
typedef std::list<Item *> Item_List;

class Item {
public:
  uint8_t  type;
  Location location;

  Item(uint8_t type, Location location) {
    this->type = TYPE_HEART;
    this->location = location;
  };

  Area get_world_area() 
    { return this->location.get_world_area(20); }

  virtual void apply_effect(Entity *entity) 
    { }
};

#endif
