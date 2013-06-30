#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "location.h"

// definitions
#define TOTAL_ENTITIES    16
#define TILESIZE          32
#define SPRITESIZE        64

#define SCREENX           640
#define SCREENY           512

#define FLOOR             0
#define ENTITY            1

#define WALK_UP           0
#define WALK_RIGHT        1
#define WALK_DOWN         2
#define WALK_LEFT         3
#define IDLE              2

#define PLAYER            0
#define MONSTER           64

#define TICKS_PER_SECOND  60
#define SKIP_TICKS        60 / TICKS_PER_SECOND
#define MAX_FRAMESKIP     10


// macros
#define CURTIME()  \
  (clock() / (float) CLOCKS_PER_SEC )

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < WORLDX && y < WORLDY)

#define player          entity[0]

typedef struct {
  uint8_t type;
  uint8_t state;
  uint8_t frame;
  uint8_t hp;
  Location location;
  Location destination;
} Entity;


// function definitions
void init_game();
void create_dungeon(unsigned int floor);
void main_game_loop();

SDL_Surface *load_sprite(const char *filename);
void draw_tile(uint8_t type, uint32_t x, uint32_t y);
void render();

void update_all_entities();
void move_all_entities();
void move_entity(Entity *actor);
void attack(Entity *actor);

int get_state(Location direction);
Entity** entities_in_area(Location area);


// sdl variables
SDL_Surface *screen;
static SDL_Surface *sprites[TOTAL_ENTITIES];
SDL_Event event;


// global game variables
long double next;

bool running = true;

int currentFloor = 0;
int loops = 0;

static Entity entity[TOTAL_ENTITIES];


int main(int argc, char **argv) {
  init_game();
  create_dungeon(currentFloor);
  main_game_loop();

  return EXIT_SUCCESS;
}

void init_game() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  next = time(NULL);

  sprites[FLOOR] = load_sprite("graphics/floor.png");
  sprites[ENTITY] = load_sprite("graphics/spritesheet.png"); 
}

/**
 * Create and then store all entities into global array.
 * The starting location is always its first destination.
 */
void create_dungeon(unsigned int floor) {

  /* the player entity is always at position [0] */
  Location location = {100, 100}; 
  Entity Player = {0, 0, 2, 10, location, location};
  entity[0] = Player;

  /* keep it simple: the floor number is how many monsters we get */
  for(int i=1; i<=currentFloor+1; i++) {
    Location location = {250, 250}; 
    Entity monster = {64, 0, 2, 10, location, location};
    entity[i] = monster;
  }

  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(FLOOR, x, y);
    }
  }
}

void main_game_loop() {
  while (running) {

    loops=0;
    while(time(NULL) > next && loops < MAX_FRAMESKIP) {
      update_all_entities();
      printf("Monster hp: %d\n", entity[1].hp);
      next += SKIP_TICKS;
      loops++;
    }

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE: case SDL_QUIT:
              running=false;
              break;
            case SDLK_w: case SDLK_UP: case SDLK_k:
              player.destination = (Location){player.location.x, 
                                              player.location.y-10};
              break;
            case SDLK_a: case SDLK_LEFT: case SDLK_h:
              player.destination = (Location){player.location.x-10, 
                                              player.location.y};
              break;
            case SDLK_s: case SDLK_DOWN: case SDLK_j:
              player.destination = (Location){player.location.x, 
                                              player.location.y+10};
              break;
            case SDLK_d: case SDLK_RIGHT: case SDLK_l:
              player.destination = (Location){player.location.x+10, 
                                              player.location.y};
              break;
            case SDLK_SPACE:
              attack(&player);
              break;
            default:
              break;
          }
      }
    }

    move_all_entities();
    render();
  }
}

SDL_Surface *load_sprite(const char filename[]) {
  SDL_Surface *temp = IMG_Load(filename);

  SDL_SetColorKey(temp, 
      (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
      SDL_MapRGB(temp->format, 0, 0, 0));


  if (temp == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Surface *sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  if (sprite == NULL) {
    printf("Failed to convert image to native format %s\n", filename);
    exit(1);
  }

  return sprite;
}

void draw_tile(uint8_t type, uint32_t x, uint32_t y) {
  SDL_Rect location = { x * TILESIZE, y * TILESIZE };
  SDL_Surface *sprite = sprites[type];

  if(SDL_BlitSurface(sprite, NULL, screen, &location) < 0) {
    printf("Error!\n");
  }
}

/**
 * Entity's frame and state both serve as indicators for which exact
 * sprite the engine needs to draw.
 *
 * If the state is at 0, or WALK_UP, then we grab a big rectangle from
 * (0,0), or the top left, till (64, 64). If it was 1, then it's from
 * (64,0) to (128,64) ... (128,0) to (192,64)
 */
void draw_entity(int type, int state, Location location, int frameModifier) {
  int frame_math = ( (SPRITESIZE * (2*state)) + SPRITESIZE * frameModifier);

  SDL_Rect spriteLocationation = { location.x, location.y };
  SDL_Rect frame = { frame_math, type, SPRITESIZE, SPRITESIZE };

  SDL_Surface *sprite = sprites[ENTITY];

  if(SDL_BlitSurface(sprite, &frame, screen, &spriteLocationation) < 0) {
    printf("Error!\n");
  }
}

void render() {
  /* draw the floor first */
  for (int x = 0; x < SCREENX; x++) {
    for (int y = 0; y < SCREENY; y++) {
      draw_tile(FLOOR, x, y);
    }
  }

  /* then draw each entity on top of the floor */
  for(int i=0; i<=currentFloor+1; i++) {
    draw_entity(entity[i].type,
        entity[i].state,
        entity[i].location,
        entity[i].frame);
  }

  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void update_all_entities() {
  for(int i=1; i<=currentFloor+1; i++) {

    /* if an entity is near the player, that entity goes to the player */
    if(locations_are_nearby(entity[1].location, player.location)) {
      entity[i].destination = player.location;
      continue;
    }

    /* if it's not, assign an entity a random destination if it has none */
    if( are_same_location( entity[i].location, entity[i].destination )) {
      entity[i].destination = random_destination_from(entity[i].location);
    }
  }
}

void move_all_entities() {
  for(int i=0; i<=currentFloor+1; i++) {
    if( !are_same_location(entity[i].location, entity[i].destination)) {
      move_entity(&entity[i]);
    }
  }
}

/** 
 * Pass the entity to be move_entityd by `reference', give the state it
 * should be, and give the location it wants to move_entity to.
 */
void move_entity(Entity *actor) {

  for(int i=0; i<=currentFloor+1; i++) {
    Entity *currentEntity = &entity[i];

    if( do_collide(actor->destination, currentEntity->location) 
        && actor != currentEntity) {
      return;
    }
  }

  Location distance = subtract_locations(actor->destination,
                                         actor->location);

  Location direction = get_direction_to(distance);
  actor->location.x += direction.x*1;
  actor->location.y += direction.y*1;
  actor->state = get_state(direction);

  if(direction.x == 0) {
    if( (!(distance.y % 10) && distance.y != 0) ) {
      /* a clean way to switch back and forth from 1 and 0 */
      actor->frame = actor->frame ? 0 : 1;
    }
  }  else {
    if( (!(distance.x % 10) && distance.x != 0) ) {
      actor->frame = actor->frame ? 0 : 1;
    }
  }
}

void attack(Entity *actor) {
  /**
   * using direction, we can determine which
   * squares to look into for an attack.
   *
   * For (0,1) -- DOWN -- the square attacked would be
   * (location + (64*0), location + (64*1)) or from its
   * location, down 64 steps.
   */
  Location direction = {0,0};
  if(actor->state == WALK_DOWN)
    direction = (Location){0,-1};
  else if(actor->state == WALK_UP)
    direction = (Location){0,1};
  else if(actor->state == WALK_RIGHT)
    direction = (Location){-1,0};
  else if(actor->state == WALK_LEFT)
    direction = (Location){1,0};

  Location areaAttacked;
  areaAttacked.x = (actor->location.x + (64 * direction.x));
  areaAttacked.y = (actor->location.y + (64 * direction.y));

  Entity **attackedEntities = entities_in_area(areaAttacked);
  //attackedEntities[0]->hp -= 10;
}

Entity** entities_in_area(Location lower) {
  /**
   * We can infer that the list returned will be of no
   * size greater than the currentFloor + 1 - 1 or just
   * currentFloor.
   *
   * We add 1 because it better represents the array
   * length, but subtract 1 because an attacking entity
   * cannot attack itself.
   *
   * Because we need to look in a square (not at a specific
   * point), we need to create bounds. The lower bound will
   * be the location given, the upper bound will be the
   * given location plus the sprite size.
   *
   * Anything in between those bounds will be considered in
   * that area.
   */

  Location upper = {lower.x + 64, lower.y + 64};

  Entity* list[TOTAL_ENTITIES] = {0};

  for(int i=0; i<=currentFloor+1; i++) {
    /*
     * The location checked here is from the top left of the entity's
     * sprite. The area that is used at the hitbox should reflect
     * this fact.
     */
    if(entity[i].location.x <= upper.x && entity[i].location.y <= upper.y &&
       entity[i].location.x >= lower.x && entity[i].location.y >= lower.y) {
      puts("Something was hit!");
      list[i] = &entity[i];
    }
  }

  return list;
}

/**
 * Return direction an entity should be facing as
 * the state based on it's current direction
 */
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
