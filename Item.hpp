#ifndef ROGUE_ITEM_HPP
#define ROGUE_ITEM_HPP

#define TYPE_HEART    128

#include <stdint.h>

#include "Entity.hpp"
#include "Location.hpp"

class Item;

typedef std::list<Item>::iterator Item_Iterator;
typedef std::list<Item> Item_List;

class Item {
public:
  uint8_t  type;
  Location location;

  Item(uint8_t type, Location location);

  /* Callback to apply to entity for whatever reason*/
  void apply_effect(Entity *entity);
};

#endif
