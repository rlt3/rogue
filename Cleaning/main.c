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
#define total_entities  16
#define TILESIZE        32
#define SPRITESIZE      64

#define SCREENX         640
#define SCREENY         512

#define FLOOR           0
#define ENTITY          1

#define WALK_UP         0
#define WALK_RIGHT      1
#define WALK_DOWN       2
#define WALK_LEFT       3
#define IDLE            2

#define PLAYER     0
#define MONSTER    64

// macros
#define CURTIME()  \
  (clock() / (float) CLOCKS_PER_SEC )

#define IN_WORLD(x, y) \
  (x >= 0 && y >= 0 && x < WORLDX && y < WORLDY)

// for ease of use
#define player          entity[0]

typedef struct {
  uint16_t x, y;
} Loc;


/**
 * For frame, instead of creating a Queue which just
 * loops from 0 to 1 and back to 0, simply do this:
 *
 * entity.frame = entity.frame ? 0 : 1;
 */

typedef struct {
  uint8_t type;
  uint8_t state;
  uint8_t frame;
  uint8_t hp;
  Loc location;
} Entity;


// function definitions
void initGame();
void createDungeon(unsigned int floor);
void gameLoop();

SDL_Surface *loadSprite(const char *filename);
void drawTile(int type, int x, int y);
void render();

void move(uint16_t x, uint16_t y);
Entity** get();


// sdl variables
SDL_Surface *screen;
SDL_Surface *sprites[total_entities] = {0};
SDL_Event event;


// global game variables
bool running = true;
int currFloor = 0;
float last = 0.0f;

Entity entity[total_entities] = {0};

int main(int argc, char **argv) {
  initGame();
  createDungeon(currFloor);
  gameLoop();

  printf("Entity at 0's hp: %d\n", entity[0].hp);
  printf("Entity at 1's hp: %d\n", entity[1].hp);

  Entity **list = get();
  list[0]->hp -= 2;
  list[1]->hp -= 2;

  puts("After:");
  printf("Entity at 0's hp: %d\n", entity[0].hp);
  printf("Entity at 1's hp: %d\n", entity[1].hp);

  return EXIT_SUCCESS;
}

void initGame() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Game", "Game");
  SDL_EnableKeyRepeat(70, 70);
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(SCREENX, SCREENY, 0, 0);

  sprites[FLOOR] = loadSprite("graphics/floor.png");
  sprites[ENTITY] = loadSprite("graphics/spritesheet.png"); 
}

// create and then store all entities into global array
void createDungeon(unsigned int floor) {

  // player is always 0
  Loc location = {100, 100}; 
  Entity Player = {0, 0, 2, 10, location};
  entity[0] = Player;

  for(int i=1; i<=floor+1; i++) {
    Loc location = {10, 10}; 
    Entity monster = {64, 0, 2, 10, location};
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

     while (SDL_PollEvent(&event)) {
        switch (event.type) {
           case SDL_KEYDOWN:
              switch(event.key.keysym.sym) {
                 case SDLK_ESCAPE: case SDL_QUIT:
                    running=false;
                    break;
                 case SDLK_w: case SDLK_UP: case SDLK_k:
                    move(player.location.x, player.location.y-10);
                    break;
                 case SDLK_a: case SDLK_LEFT: case SDLK_h:
                    move(player.location.x-10, player.location.y);
                    break;
                 case SDLK_s: case SDLK_DOWN: case SDLK_j:
                    move(player.location.x, player.location.y+10);
                    break;
                 case SDLK_d: case SDLK_RIGHT: case SDLK_l:
                    move(player.location.x+10, player.location.y);
                    break;
                 default:
                    break;
              }
        }
     }

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

void drawTile(int type, int x, int y) {
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
   for (int x = 0; x < SCREENX; x++) {
      for (int y = 0; y < SCREENY; y++) {
         drawTile(FLOOR, x, y);
      }
   }

   for(int i=0; i<=currFloor+1; i++) {
      drawEntity(entity[i].type,
                 entity[i].state,
                 entity[i].location,
                 entity[i].frame);
   }

   SDL_UpdateRect(screen, 0, 0, 0, 0);
}

// move entity unless something's in the way
void move(uint16_t x, uint16_t y) {
   int nx = (( x+(64/2))/32 );
   int ny = (( y+(64))/32 );

   bool collision = false;
   for(int i=1; i<=currFloor+1; i++) {
      Loc location = entity[i].location;
      int wx = (( location.x+(64/2))/32 );
      int wy = (( location.y+(64))/32 );

      if(wx == nx && wy == ny) {
         collision = true;
         break;
      }
   }

   if(collision) {
      return;
   } else {
      player.location.x = x;
      player.location.y = y;
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
