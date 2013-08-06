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
  uint8_t   frames;

  uint8_t   hp;
  uint8_t   strength;
  uint8_t   speed;
  bool      idle;

  Location  location;
  Location  destination;

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
  if (entity->state > 3) {
    return;
  }

  entity->idle = false;

  if (state == ATTACKING && entity->state < 4) {
    entity->state += 4;
    entity->frames = 2;
    return;
  }

  entity->state = state;

  switch(state) {
  case WALK_UP:
    set_destination(entity, 0, (-10 * entity->speed));
    break;
  case WALK_DOWN:
    set_destination(entity, 0, (10 * entity->speed));
    break;
  case WALK_LEFT:
    set_destination(entity, (-10 * entity->speed), 0);
    break;
  case WALK_RIGHT:
    set_destination(entity, (10 * entity->speed), 0);
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

  Location destination = subtract_locations(entity->destination,
                                            entity->location);
  Location direction = get_direction_to(destination);

  Location next_step = {
    entity->location.x + direction.x * entity->speed,
    entity->location.y + direction.y * entity->speed
  };
  
  while (node != NULL) {
    if(do_collide(next_step, node->location) 
       && entity != node) {
      return;
    }
    node = node->next;
  }

  entity->location = next_step;
  entity->state = get_state(direction);
  entity->idle = false;
}

void entity_attacks(Entity* entity, Entity *start, int level) {
  /* Translate back to a WALK_* from ATTACK_* */
  int state = (entity->state > 3 ? entity->state - 4 : entity->state);

  /* Get direction from entity's state */
  Location direction = {0,0};
  if(state == WALK_DOWN)
    direction = (Location){0,1};
  else if(state == WALK_UP)
    direction = (Location){0,-1};
  else if(state == WALK_RIGHT)
    direction = (Location){1,0};
  else if(state == WALK_LEFT)
    direction = (Location){-1,0};

  /*
   * Need four locations in specific: the attacking entity's
   * attack box points at the top-left and then bottom-right.
   * Then the opposing entity's hitbox, from the top-left
   * and then bottom-right.
   *
   * Then we test if they collide at any point.
   */

  Area attack_box;
  Area hit_box;

  attack_box.a = (Location) {
    (entity->location.x + (direction.x != 0 ? direction.x * 48 : 32)),
    (entity->location.y + (direction.y != 0 ? direction.y * 48 : 32))
  };

  attack_box.b = (Location) {
    attack_box.a.x + (direction.x == 0 ? 16 : 48),
    attack_box.a.y + (direction.y == 0 ? 16 : 48)
  };

  Entity *node = start;
  while (node != NULL) {
    hit_box.a = (Location) {node->location.x + 16, node->location.y + 16};
    hit_box.b = (Location) {hit_box.a.x + 48, hit_box.a.y + 48};

    if(areas_intersect(attack_box, hit_box) && node != entity) {
      node->hp -= entity->strength;
    }

    node = node->next;
  }
}

#endif
