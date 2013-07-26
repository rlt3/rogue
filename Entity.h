#ifndef ROGUE_ENTITY_H
#define ROGUE_ENTITY_H

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

#include "Location.h"

typedef struct Entity {
  uint8_t   type;
  uint8_t   state;
  uint8_t   hp;
  uint8_t   frames;
  Location  location;
  Location  destination;
  bool      idle;
} Entity;

void set_destination(Entity *entity, uint32_t x, uint32_t y) {
  entity->destination.x = entity->location.x + x;
  entity->destination.y = entity->location.y + y;
}

void update_entity(Entity *entity, uint8_t state) {
  entity->idle = false;

  if (state == ATTACKING) {
    entity->state += 4;
    entity->frames = 2;
    return;
  }

  entity->state = state;

  switch(state) {
  case WALK_UP:
    set_destination(entity, 0, -10);
    break;
  case WALK_DOWN:
    set_destination(entity, 0, 10);
    break;
  case WALK_LEFT:
    set_destination(entity, -10, 0);
    break;
  case WALK_RIGHT:
    set_destination(entity, 10, 0);
    break;
  default:
    break;
  }

}

int get_state(Location direction) {
  int state = IDLE;

  if(direction.x == 0 && direction.y == 1)
    state = WALK_DOWN;
  else if(direction.x == 0 && direction.y == -1)
    state = WALK_UP;
  else if(direction.x == 1 && direction.y == 0)
    state = WALK_RIGHT;
  else if(direction.x == -1 && direction.y == 0)
    state = WALK_LEFT;

  return state;
}

void move_entity(Entity *entity, Entity entities[], int currentFloor) {
  for(int i=0; i<=currentFloor; i++) {
    if(do_collide(entity->destination, entities[i].location) 
       && entity != &entities[i]) {
      return;
    }
  }
  Location destination = subtract_locations(entity->destination,
                                            entity->location);
  Location direction = get_direction_to(destination);

  entity->location.x += direction.x*1;
  entity->location.y += direction.y*1;

  entity->state = get_state(direction);
  entity->idle = false;
}

void entity_attacks(Entity* entity, Entity entities[], int level) {

  Location direction = {0,0};
  if(entity->state == WALK_DOWN)
    direction = (Location){0,1};
  else if(entity->state == WALK_UP)
    direction = (Location){0,-1};
  else if(entity->state == WALK_RIGHT)
    direction = (Location){1,0};
  else if(entity->state == WALK_LEFT)
    direction = (Location){-1,0};

  Location lower = {
    (entity->location.x + (direction.x != 0 ? direction.x * 64 : 0)),
    (entity->location.y + (direction.y != 0 ? direction.y * 64 : 0))
  };

  Location upper = {lower.x + 64, lower.y + 64};

  for(int i=0; i<=level; i++) {
    /* Create a `area' to test intersection of the attack box */
    Location eLower = {entity[i].location.x, entity[i].location.y};
    Location eUpper = {entity[i].location.x + 64, entity[i].location.y + 64};

    if(eLower.x < upper.x && eUpper.x > lower.x &&
       eLower.y < upper.y && eUpper.y > lower.y
       && &entities[i] != entity) {
      entity[i].hp -= 5;
    }
  }
}

#endif
