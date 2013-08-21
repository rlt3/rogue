#include "Game.h"

/* Public Functions */

struct Game* new_game();
void cleanup_game(struct Game* game);
void update(struct Game*, unsigned time);
void handle(struct Game*);
void render(struct Game*);

/* Private Functions */

static void create_player(struct Game*);
static void create_monsters(struct Game*);
static void create_dungeon(struct Game*);
static void create_level(struct Game*);
static void move_all_entities(struct Game*);
static void draw_tile(struct Game*, uint8_t type, uint32_t x, uint32_t y);
static void draw_entity(struct Entity *entity, Spritesheet sprite);

/* Definitions */

struct Game* new_game() {
  struct Game *game = malloc(sizeof(struct Game));

  *game = (struct Game) {
    .on             = true,
    .level          = 1,
    .last_time      = 0,
    .update_rate    = 500,
    .spritesheet    = load_sheet("Graphics/loz.png"),
    .update         = &update,
    .handle         = &handle,
    .render         = &render
  };

  create_level(game);

  return game;
}

void cleanup_game(struct Game* game) {
  window_free(&game->spritesheet);
  
  struct Entity *prev;
  struct Entity *node = game->entities_head;
  do {
    prev = node;
    node = node->next;
    free(prev);
  } while (node != NULL);

  free(game);
}

void update(struct Game *self, unsigned now) {
  //Entity_Iterator entity;
  //Entity_Iterator end = self->entities.end();

  //for (entity = self->entities.begin(); entity != end; ++entity) { 
  // entity->update(now);
  //}

  //check_all_entities(now);

  //if (self->player->hp <= 0) {
  //  self->player->hp = 10;
  //  puts("You lose!");
  //  self->on = false;
  //}

  ///* If only the player exists, create next level */
  //if (self->entities.size() == 1) {
  //  self->level++;
  //  self->create_dungeon();
  //}
}

static void move_entity(struct Entity *entity, struct Entity *head) {
  if (location_is_same(entity->location, entity->destination)) {
    return;
  }

  struct Location direction = get_direction(entity->destination,
                                            entity->location);

  struct Location next_step = {
    entity->location.x + direction.x * entity->speed,
    entity->location.y + direction.y * entity->speed
  };

  struct Entity *other = head;
  while (other != NULL) {
    if (locations_collide(entity->location, other->location) 
        && entity != other) {
      return;
    }
    other = other->next;
  }

  entity->move(entity, next_step, direction);
}

void handle(struct Game *self) {
  struct Entity *entity;
  struct Entity *next = self->entities_head;

  do {
    entity = next;
    next   = next->next;

    /* need a way to handle collisions all at one point
     * in the code. Also a way to have location and direction
     * in one structure.
     */

    handle_death(entity);
    move_entity(entity, self->entities_head);

  } while (next != NULL);

  //for (entity = self->entities.begin(); entity != end; ++entity) { 

  //  /* The player updates itself based on input, no need to update */
  //  if (self->player ==entity) { continue; }

  //  /* Display the entire attack animation */
  //  if (entity->state > 3)      { continue; }

  //  if (entity->hp <= 0) {
  //    self->items.insert(self->items.begin(), new Heart(entity->location));
  //    //deleteentity;
  //    self->entities.remove(*entity);
  //  }

  //  if (entity->location.is_same(entity->destination)) {
  //    Location dest =entity->location.new_destination(entity->speed);
  //    if (IN_WORLD(dest.x, dest.y)) {
  //     entity->destination = dest;
  //    }
  //  }
  //    
  //  if ((now - last_time) < update_rate) { continue; }
  //  last_time = now;

  //  /* Sort entity locations so entities get drawn the right way: top to down */
  //  //entities.sort(Entity::sort_entities);

  //  /* If we're here, then we're attacing/moving towards the player, etc */
  //  if (entity->location.is_nearby(self->player->location)) {
  //    if (entity->location.is_adjacent(self->player->location)) {
  //     entity->set_state(ATTACKING);
  //     entity->attack(self->entities);
  //    } else {
  //     entity->destination = self->player->location;
  //    }
  //  }
  //}
}

void render(struct Game *self) {
  window_fill(0xCC, 0xCC, 0xCC);

  struct Entity *entity = self->entities_head;
  while (entity != NULL) {
    draw_entity(entity, self->spritesheet);
    entity = entity->next;
  }

  window_display();

  ///* Draw the health bar */
  //int health = self->player->hp;
  //for (int i = 1; i <= health; i++) {
  //  draw_tile(HEART, (i*24), (SCREENY - 24));
  //  //draw_tile(HEART, (i*20), (SCREENY - 20));
  //}
  //
  ////Item_Iterator item;
  ////Item_Iterator item_end = self->items.end();
  ////for (item = self->items.begin(); item != item_end; ++item) { 
  ////  draw_tile((*item)->type, (*item)->location.x, (*item)->location.y);
  ////}
}

static void create_player(struct Game* game) {
  game->player = malloc(sizeof(struct Entity));
 *game->player = new_player();
  game->entities_head = game->player;
}

static void create_monsters(struct Game* game) {
  //
}

static void create_level(struct Game* game) {
  create_player(game);
  create_monsters(game);
}

static void move_all_entities(struct Game *self) {
  //Entity_Iterator entity;
  //Entity_Iterator end = self->entities.end();

  //for (entity = self->entities.begin(); entity != end; ++entity) { 
  //  if (!entity->location.is_same(entity->destination)) {
  //   entity->move(entities);
  //  }
  //}
}

static void create_dungeon(struct Game *self) {
  ///* If we don't do self, the player multiplies */
  //if (self->entities.size() > 0) {
  //  // clear list
  //}

  //int i;
  //for (i = 1; i <= self->level; i++) {
  //  self->entities.insert(
  //      self->entities.begin(), 
  //      Entity(TYPE_MONSTER, Location(i*128, i*128))
  //  );
  //}

  ///* 
  // * We have a pointer just to the player so that we can manipulate the 
  // * list of entities in any fashion and not lose track of the most
  // * important entity
  // */

  ////self->player = new Entity(TYPE_PLAYER, Location(144, 144));
  //self->entities.insert(self->entities.begin(), Entity(TYPE_PLAYER, Location(144, 144)));
  //self->player = self->entities.begin();
}


static void draw_tile(struct Game *self, uint8_t type, uint32_t x, uint32_t y) {
  //int size = (type > 128 ? 32 : 20);
  //int size = 32;

  //SDL_Rect location     = {x, y};
  //SDL_Rect mask         = {0, type, size, size};
  //SDL_Surface *sprite   = self->spritesheet;

  //draw(sprite, &mask, Screen::surface, &location);
}

static void draw_entity(struct Entity *entity, Spritesheet sprite) {
  Area location = (SDL_Rect){entity->location.x, entity->location.y};

  Area frame = { 
    .x = (32 * entity->state) + (16 * entity->frame),
    .y = entity->type, 
    .w = SPRITESIZE, 
    .h = SPRITESIZE
  };

  window_draw(sprite, &frame, &location); 
}

//void draw_entity(struct Game *self, Entity *entity) {
  //SDL_Rect location     = {entity->location.x, entity->location.y};
  //SDL_Rect location;

  //if (entity->state > 3) {
  //  location = (SDL_Rect){
  //        entity->location.x + entity->offsets[entity->state].x, 
  //        entity->location.y + entity->offsets[entity->state].y
  //  };
  //} else {
  //  location = (SDL_Rect){entity->location.x, entity->location.y};
  //}

  //SDL_Surface *sprite   = spritesheet;

  ///* 
  // * So, we don't have to load a large amount of SDL_Rects, we use math based 
  // * on an Entity's state/type/frame to see where on the sprite sheet we are 
  // * getting the image.
  // */

  ////SDL_Rect frame = { 
  ////  (128 * entity->state) + (64 * entity->frame),
  ////  entity->type, SPRITESIZE, SPRITESIZE 
  ////};
  //
  //SDL_Rect frame;
  //    //(entity->type + 16) + (16 * entity->frame),

  //if (entity->state > 3) {
  //  frame = (SDL_Rect){ 
  //    (32 * (entity->state % 4)),
  //    (entity->type + 16) + (32 * entity->frame),
  //    SPRITESIZE*2, SPRITESIZE*2
  //  };
  //} else {
  //  frame = (SDL_Rect){ 
  //    (32 * entity->state) + (16 * entity->frame),
  //    entity->type, SPRITESIZE, SPRITESIZE
  //  };
  //}
  //draw(sprite, &frame, Screen::surface, &location); 
//}
