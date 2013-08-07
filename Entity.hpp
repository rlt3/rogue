#ifndef ROGUE_ENTITY_HPP
#define ROGUE_ENTITY_HPP

#define WALK_UP           0
#define WALK_RIGHT        1
#define WALK_DOWN         2
#define WALK_LEFT         3

#define ATTACK_UP         4
#define ATTACK_RIGHT      5
#define ATTACK_DOWN       6
#define ATTACK_LEFT       7

#define ATTACKING         8
#define IDLE              2

#define TYPE_PLAYER       0
#define TYPE_MONSTER      64

#include <stdint.h>
#include <list>

#include "Location.hpp"

class Entity;

typedef std::list<Entity*>::iterator Entity_Iterator;
typedef std::list<Entity*> Entity_List;

class Entity {
public:
  uint8_t   hp;
  uint8_t   strength;
  uint8_t   speed;

  uint8_t   type;
  uint8_t   state;
  uint8_t   frame;
  uint8_t   do_frames;
  bool      idle;

  Location  location;
  Location  destination;

  Entity(uint8_t type, Location location);

  void set_destination(uint32_t x, uint32_t y);
  void update(uint8_t state);

  void move(Entity_List entities);
  void attack(Entity_List &entities);

  static int get_state(Location direction);
  static Location get_direction(uint8_t state);
};

#endif
