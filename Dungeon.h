#ifndef DUNGEON_H
#define DUNGEON_H
#include "defs.h"
#include "Monster.h"

class Dungeon
{
   public:
      Dungeon();
      void draw(SDL_Surface *screen)
      void updateEntities(int turns=1);
   protected:
      //Monster* Monsters[MAP_HEIGHT][MAP_WIDTH]; 
      SLD_Surface *brickImage, *backgroundImage;
      Monster *test1, *test2, *test3;
      int floor;

      Location moveLocation(Location location);
      void drawMap(SDL_Surface *screen);
      void drawEntities(SDL_Surface *screen);
      void generateMap(long seed=NULL);
      void generateEntities(long seed=NULL);
      bool validLocation(Location location);
      int  Map[MAP_HEIGHT][MAP_WIDTH]; 
      int  getTile(Location location);
};
#endif
