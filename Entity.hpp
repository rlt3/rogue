/*
 * Our entities are all of our `living' things that move around in the game.
 *
 * There is a list of Entity Pointers that get manipulated as they walk, move,
 * or attack. The reason I used a list of Entity pointers (rather than just a
 * list of Entities) is that we need to do pointer comparison at points.
 *
 * So, when an entity attacks, it loops through all of the entities to see if
 * it hit anyone of them. An entitiy that attacked would almost certainly `hit
 * itself' if we didn't have pointer comparison.
 *
 * The same goes for movement and collision. 
 *
 * We also need to use a list of Entity Pointers because the player character
 * needs to be tracked at all times while in the list. The list gets sorted and
 * the positions of the entities inside are not static. Therefore, being able
 * to update the player independently from the rest of the entities (while
 * still being inside the list), requires the list to have pointers. This all
 * hinges on me not knowing a better way to do this.
 */

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
#define TYPE_MONSTER      112

#include <stdint.h>
#include <list>

#include "Location.hpp"

class Entity;

typedef std::list<Entity>::iterator Entity_Iterator;
typedef std::list<Entity> Entity_List;

class Entity {
public:
  uint8_t   type;
  uint8_t   state;

  uint8_t   hp;
  uint8_t   strength;
  uint8_t   speed;
  bool      idle;

  uint8_t   frame;
  int   do_frames;
  uint8_t   framerate;
  uint32_t  last_time;

  Location  offsets[8];

  Location  location;
  Location  destination;

  Entity(uint8_t type, Location location);

  void update(unsigned current_time);
  void set_destination(uint32_t x, uint32_t y);
  void set_state(uint8_t state);
  void move(Entity_List entities);
  void attack(Entity_List &entities);
  bool is_equal(Entity other);
  
  Area get_world_area();

  bool operator==(const Entity& rhs);

  static bool sort_locations(Entity *first, Entity *second);
  static int get_state(Location direction);
  static Location get_direction(uint8_t state);
  static bool sort_entities(const Entity * const & first, 
                             const Entity * const & second);
};

#endif
