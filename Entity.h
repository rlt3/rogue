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

void update_entity(Entity *entity, uint8_t state);
void entity_attacks(Entity* entity, Entity entities[],
                    Location upper, Location lower);

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
    entity->location.y -= 10;
    break;
  case WALK_DOWN:
    entity->location.y += 10;
    break;
  case WALK_LEFT:
    entity->location.x -= 10;
    break;
  case WALK_RIGHT:
    entity->location.x += 10;
    break;
  default:
    break;
  }

}

void entity_attacks(Entity* entity, Entity entities[],
                    Location upper, Location lower) {
}

#endif
