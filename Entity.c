#include "Entity.h"

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
    .state       = IDLE,
    .hp          = 10,
    .frame       = 0,
    .idle        = true,
    .location    = ((struct Location){i*128, i*128}),
    .destination = ((struct Location){i*128, i*128}),
    .next        = NULL
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

