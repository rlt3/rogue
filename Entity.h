#ifndef ENTITY_LOCATION_H
#define ENTITY_LOCATION_H

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

#include <stdlib.h>
#include <stdbool.h>
#include "Location.h"

struct Entity {
  uint8_t type;
  uint8_t state;
  uint8_t hp;
  uint8_t frame;
  bool    idle;

  struct Location location;
  struct Location destination;

  struct Entity *next;
};

void add_entity(struct Entity **head);
void remove_entity(struct Entity **head, struct Entity *old);
void remove_second_entity(struct Entity **head);

#endif
