#include "Item.hpp"


Item::Item(uint8_t type, Location location) {
  this->type = type;
  this->location = location;
}

void Item::apply_effect(Entity *entity) {
  switch(this->type) {
  case TYPE_HEART:
    entity->hp += 2;
    break;
  }
}
