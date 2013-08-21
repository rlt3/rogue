#include "Entity.h"

void set_state(struct Entity*, uint8_t);
void move(struct Entity* self, struct Location next_step, struct Location direction);
static void set_destination(struct Entity* self, int x, int y);
static int get_state(struct Location direction);

struct Entity new_player() {
  struct Entity player = (struct Entity){
    .type        = 0,
    .speed       = 1,
    .hp          = 10,
    .state       = IDLE,
    .idle        = true,
    .frame       = 0,
    .framerate   = 250,
    .do_frames   = 0,
    .location    = ((struct Location){64, 64}),
    .destination = ((struct Location){64, 64}),
    .next        = NULL,
    .set_state   = &set_state,
    .move        = &move
  };

  return player;
}

void add_entity(struct Entity **head) {
  int i = 0;

  (*head)->location.x += 10;

  struct Entity *node = *head;
  while (node->next != NULL) {
    node = node->next;
    i++;
  }

  node->next = malloc(sizeof(struct Entity));
  *node->next = (struct Entity){
    .type        = 0,
    .speed       = 1,
    .hp          = 10,
    .state       = IDLE,
    .idle        = true,
    .frame       = 0,
    .framerate   = 250,
    .do_frames   = 0,
    .location    = ((struct Location){i*128, i*128}),
    .destination = ((struct Location){i*128, i*128}),
    .next        = NULL,
    .set_state   = &set_state
  };
}

void remove_entity(struct Entity **head, struct Entity *old) {
  struct Entity *prev = *head;
  struct Entity *node = (*head)->next;

  while (node != NULL) {
    if (node == old) {
      prev->next = node->next;
      free(node);
      break;
    } else {
      prev = node;
      node = node->next;
    }
  }
}

void remove_second_entity(struct Entity **head) {
  struct Entity *node = (*head)->next;

  if (node == NULL) { return; }

  struct Entity *next = node->next;
  (*head)->next = next;
  free(node);
}

void set_state(struct Entity *self, uint8_t state) {
  self->idle = false;

  /* If they are already attacking return, so they can spam space */
  if (self->state > 3 && state > 3) { return; }

  /* Set state to +4 so it corresponds to their walking direction */
  if (state == ATTACKING) {
    self->state += 4;
    self->framerate = 50;
    self->do_frames = 3;
    self->frame = 0;
    return;
  }

  self->state = state;

  switch(state) {
  case WALK_UP:
    set_destination(self, 0, (-10 * self->speed));
    break;

  case WALK_DOWN:
    set_destination(self, 0, (10 * self->speed));
    break;

  case WALK_LEFT:
    set_destination(self, (-10 * self->speed), 0);
    break;
   
  case WALK_RIGHT:
    set_destination(self, (10 * self->speed), 0);
    break;
    
  default:
    break;
  }
}

void move(struct Entity* self, struct Location next_step, struct Location direction) {
  self->location = next_step;
  self->state    = get_state(direction);
  self->idle     = false;
}

static void set_destination(struct Entity *self, int x, int y) {
  self->destination.x = self->location.x + x;
  self->destination.y = self->location.y + y;
}

static int get_state(struct Location direction) {
  int state = IDLE;

  if (direction.x == 0 && direction.y == 1) {
    state = WALK_DOWN;
  } else if (direction.x == 0 && direction.y == -1) {
    state = WALK_UP;
  } else if (direction.x == 1 && direction.y == 0) {
    state = WALK_RIGHT;
  } else if (direction.x == -1 && direction.y == 0) {
    state = WALK_LEFT;
  }

  return state;
}
