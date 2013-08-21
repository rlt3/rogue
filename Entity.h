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
  uint8_t speed;
  uint8_t hp;

  uint8_t state;
  bool    idle;

  uint8_t frame;
  uint8_t framerate;
  uint8_t do_frames;

  struct Location location;
  struct Location destination;

  struct Entity *next;

  void (*move)(struct Entity*, struct Location next_step, struct Location direction);
  void (*set_state)(struct Entity*, uint8_t);
};

struct Entity new_player();

void add_entity(struct Entity **head);
void remove_entity(struct Entity **head, struct Entity *old);
void remove_second_entity(struct Entity **head);

#endif
