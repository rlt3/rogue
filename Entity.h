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
  struct Entity  *next;
} Entity;

void add_entity(Entity *start, Entity new) {
  Entity *next = start->next;
  new.next = next;
  start->next = &new;
}

/*
 * We will never delete the first Entity in the
 * list because the first Entity is always the
 * player.
 */
void remove_entity(Entity *start, Entity *old) {
  Entity *prev = start;
  Entity *node = start->next;
  while (node != NULL) {
    if (node == old) {
      prev->next = node->next;
      node = NULL;
    } else {
      prev = node;
      node = node->next;
    }
  }
}

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

void move_entity(Entity *entity, Entity *start, int currentFloor) {
  Entity *node = start;
  while (node != NULL) {
    if(do_collide(entity->destination, node->location) 
       && entity != node) {
      return;
    }
    node = node->next;
  }

  Location destination = subtract_locations(entity->destination,
                                            entity->location);
  Location direction = get_direction_to(destination);

  entity->location.x += direction.x*1;
  entity->location.y += direction.y*1;

  entity->state = get_state(direction);

  entity->idle = false;
}

void entity_attacks(Entity* entity, Entity *start, int level) {
  /* Get direction from entity's state */
  Location direction = {0,0};
  if(entity->state == WALK_DOWN)
    direction = (Location){0,1};
  else if(entity->state == WALK_UP)
    direction = (Location){0,-1};
  else if(entity->state == WALK_RIGHT)
    direction = (Location){1,0};
  else if(entity->state == WALK_LEFT)
    direction = (Location){-1,0};

  /* 
   * Need four locations in specific: the attacking entity's
   * attack box points at the top-left and then bottom-right.
   * Then the opposing entity's hitbox, from the top-left
   * and then bottom-right.
   *
   * Then we test if they collide at any point.
   */

  Location lower = {
    (entity->location.x + (direction.x != 0 ? direction.x * 64 : 0)),
    (entity->location.y + (direction.y != 0 ? direction.y * 64 : 0))
  };

  Location upper = {lower.x + 64, lower.y + 64};

  Entity *node = start;
  while (node != NULL) {
    Location eLower = {node->location.x, node->location.y};
    Location eUpper = {node->location.x + 64, node->location.y + 64};

    if(eLower.x < upper.x && eUpper.x > lower.x &&
       eLower.y < upper.y && eUpper.y > lower.y
       && node != entity) {
      node->hp -= 5;
    }
    node = node->next;
  }
}

#endif
