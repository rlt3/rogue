#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

//gcc -o out main.c ../SDLlib/SDL_Main/SDLMain.m -framework SDL -framework SDL_image -framework Cocoa -std=c99

// definitions
#define total_entities    16
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

int sgn(int val) {
    return (0 < val) - (val < 0);
}


// game-object types
typedef struct {
  uint32_t x, y;
} Loc;

typedef struct {
  uint8_t type;
  uint8_t state;
  uint8_t frame;
  uint8_t hp;
  Loc location;
  Loc destination;
} Entity;


// function definitions
void initGame();
void createDungeon(unsigned int floor);
void gameLoop();

SDL_Surface *loadSprite(const char *filename);
void drawTile(uint8_t type, uint32_t x, uint32_t y);
void render();

bool sameLoc(Loc h, Loc j);
Loc randomDestinationFrom(Loc now);
void updateEntities();
void moveEntities();
void walk(Entity *actor, uint8_t state, uint32_t x, uint32_t y);
int getState(Loc direction);
Entity** get();


// sdl variables
SDL_Surface *screen;
SDL_Surface *sprites[total_entities] = {0};
SDL_Event event;


// global game variables
long double next;

bool running = true;

int currFloor = 0;
int loops = 0;

Entity entity[total_entities] = {0};


int main(int argc, char **argv) {
  initGame();
  createDungeon(currFloor);
  gameLoop();

  //Entity **list = get();
  //list[0]->hp -= 2;
  //list[1]->hp -= 2;

  return EXIT_SUCCESS;
}


void initGame() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  next = time(NULL);

  sprites[FLOOR] = loadSprite("graphics/floor.png");
  sprites[ENTITY] = loadSprite("graphics/spritesheet.png"); 
}


// create and then store all entities into global array
// current location is always its destination
void createDungeon(unsigned int floor) {

  // player is always 0
  Loc location = {100, 100}; 
  Entity Player = {0, 0, 2, 10, location, location};
  entity[0] = Player;

  for(int i=1; i<=currFloor+1; i++) {
    Loc location = {250, 250}; 
    Entity monster = {64, 0, 2, 10, location, location};
    entity[i] = monster;
  }

   for (int x = 0; x < SCREENX; x++) {
      for (int y = 0; y < SCREENY; y++) {
         drawTile(FLOOR, x, y);
      }
   }

   render();
}


void gameLoop() {
  while (running) {
     
      loops=0;
      while(time(NULL) > next && loops < MAX_FRAMESKIP) {
         updateEntities();
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
                    walk(&player, WALK_UP, player.location.x, player.location.y-10);
                    break;
                 case SDLK_a: case SDLK_LEFT: case SDLK_h:
                    walk(&player, WALK_LEFT, player.location.x-10, player.location.y);
                    break;
                 case SDLK_s: case SDLK_DOWN: case SDLK_j:
                    walk(&player, WALK_DOWN, player.location.x, player.location.y+10);
                    break;
                 case SDLK_d: case SDLK_RIGHT: case SDLK_l:
                    walk(&player, WALK_RIGHT, player.location.x+10, player.location.y);
                    break;
                 default:
                    break;
              }
        }
     }

   moveEntities();
   render();
  }
}


SDL_Surface *loadSprite(const char filename[]) {
  SDL_Surface *temp = IMG_Load(filename);

  SDL_SetColorKey(temp, 
                  (SDL_SRCCOLORKEY|SDL_RLEACCEL), 
                  SDL_MapRGB(temp->format, 0, 0, 0));
  

  if (temp == NULL) {
    printf("Error: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Surface *sprite;
  sprite = SDL_DisplayFormat(temp);

  SDL_FreeSurface(temp);

  if (sprite == NULL) {
    printf("Failed to convert image to native format %s\n", filename);
    exit(1);
  }

  return sprite;
}


void drawTile(uint8_t type, uint32_t x, uint32_t y) {
   SDL_Rect location = { x * TILESIZE, y * TILESIZE };
   SDL_Surface *sprite = sprites[type];

   if(SDL_BlitSurface(sprite, NULL, screen, &location) < 0) {
      printf("Error!\n");
   }
}



void drawEntity(int type, int state, Loc location, int frameModifier) {
   int frame_math = ( (SPRITESIZE * (2*state)) + SPRITESIZE * frameModifier);

   SDL_Rect spriteLocation = { location.x, location.y };
   SDL_Rect frame = { frame_math, type, SPRITESIZE, SPRITESIZE };

   SDL_Surface *sprite = sprites[1];

   if(SDL_BlitSurface(sprite, &frame, screen, &spriteLocation) < 0) {
      printf("Error!\n");
   }
}


void render() {
   /** draw the floor **/
   for (int x = 0; x < SCREENX; x++) {
      for (int y = 0; y < SCREENY; y++) {
         drawTile(FLOOR, x, y);
      }
   }

   /** draw each entity **/
   for(int i=0; i<=currFloor+1; i++) {
      drawEntity(entity[i].type,
                 entity[i].state,
                 entity[i].location,
                 entity[i].frame);
   }

   SDL_UpdateRect(screen, 0, 0, 0, 0);
}

bool sameLoc(Loc h, Loc j) {
   bool equal = false;
   if(h.x == j.x && h.y == j.y) {
      equal = true;
   }
   return equal; 
}

Loc randomDestinationFrom(Loc now) {
   unsigned short int i = rand() % 5;

   int direction[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };
   int magnitude[5][2] = { {35,30}, {30,-35}, {0,0}, {-30,35}, {35,30} };

   Loc destination;
   destination.x = now.x + direction[i][0]*magnitude[i][0];
   destination.y = now.y + direction[i][1]*magnitude[i][1];

   return destination;
}

void updateEntities() {
   for(int i=1; i<=currFloor+1; i++) {
      if(sameLoc(entity[i].location,entity[i].destination)) {
         entity[i].destination = randomDestinationFrom(entity[i].location);
         
         //printf("Location is (%d,%d) ", entity[i].location.x,
         //                                    entity[i].location.y);
         //printf("Destination is (%d,%d)\n", entity[i].destination.x,
         //                                    entity[i].destination.y);
      }
   }
}

void moveEntities() {
   for(int i=1; i<=currFloor+1; i++) {
      if(!sameLoc(entity[i].location,entity[i].destination)) {
         Loc distance;
         distance.x = entity[i].destination.x - entity[i].location.x;
         distance.y = entity[i].destination.y - entity[i].location.y;

         Loc direction;
         if(distance.x != 0) {
            direction.x = sgn(distance.x);
            direction.y = 0;
         }  else {
            direction.x = 0;
            direction.y = sgn(distance.y);
         }

         //Location destination = entity[i].location;
         //destination.x += (entity[i].location.x != entity[i].destination.x) ? direction.x*1 : 0;
         //destination.y += (entity[i].location.y != entity[i].destination.y) ? direction.y*1 : 0;
         entity[i].state = getState(direction);

         int diffx = entity[i].destination.x - entity[i].location.x;
         int diffy = entity[i].destination.y - entity[i].location.y;
         if(direction.x == 0) {
            if( (!(diffy % 10) && diffy != 0) ) {
               entity[i].frame = entity[i].frame ? 0 : 1;
            }
         }  else {
            if( (!(diffx % 10) && diffx != 0) ) {
               entity[i].frame = entity[i].frame ? 0 : 1;
            }
         }

         entity[i].location.x += (entity[i].location.x != entity[i].destination.x) ? direction.x*1 : 0;
         entity[i].location.y += (entity[i].location.y != entity[i].destination.y) ? direction.y*1 : 0;

         //walk(&entity[i], state, direction.x, direction.y);
      }
   }
}

/** 
 * Pass the entity to be walkd by `reference', give the state it
 * should be, and give the location it wants to walk to.
 */
void walk(Entity *actor, uint8_t state, uint32_t x, uint32_t y) {
   int nx = (( x+(64/2))/32 );
   int ny = (( y+(64))/32 );

   bool collision = false;
   //for(int i=1; i<=currFloor+1; i++) {
   //   Loc location = entity[i].location;
   //   int wx = (( location.x+(64/2))/32 );
   //   int wy = (( location.y+(64))/32 );

   //   if(wx == nx && wy == ny) {
   //      collision = true;
   //      break;
   //   }
   //}

   if(collision) {
      return;
   } else {
      actor->location.x = x;
      actor->location.y = y;
      actor->state = state;

      // a clean way to switch back and forth from 1 and 0
      actor->frame = actor->frame ? 0 : 1;
   }
}


// prototype to get all entities as a pointer to their
// location in the global array
Entity** get() {
   Entity* list[total_entities] = {0};

   for(int i=0; i<=currFloor+1; i++) {
      list[i] = &entity[i];
   }

   return list;
}

int getState(Loc direction) {
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
