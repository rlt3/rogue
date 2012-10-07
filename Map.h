#ifndef MAP_H
#define MAP_H
#include "Entity.h"

#define MAP_WIDTH       20
#define MAP_HEIGHT      15
#define OFFSET          1

#define TILE_FLOOR      0
#define TILE_WALL       1
#define TILE_GRASS      34
#define TILE_OPENDOOR   47

#define DRAGON_CHAR     71

class Map
{
   public:
      void draw(void);  // draw the goddamn map
      static int array[MAP_HEIGHT][MAP_WIDTH];
      static int getTile(Location location);
};

void Map::draw(void)
{
   clear();
   for (int y=OFFSET;y<=MAP_HEIGHT;y++)
   {
      for (int x=OFFSET;x<=MAP_WIDTH;x++)
      {
         //mvaddch(y,x,array[y-OFFSET][x-OFFSET]);
         init_pair(2, COLOR_RED, COLOR_BLACK);
         attron(COLOR_PAIR(2)); 
         mvaddch(y,x,Map::getTile(Location(x-OFFSET,y-OFFSET)));//array[y-OFFSET][x-OFFSET]);
         attroff(COLOR_PAIR(2));
         //switch( array[y-OFFSET][x-OFFSET] )
         //{
         //   case TILE_FLOOR:
         //      mvaddch(y,x,46);
         //      break;

         //   case TILE_WALL:
         //      mvaddch(y,x,35);
         //      break;

         //   default:
         //      init_pair(2, COLOR_RED, COLOR_BLACK);
         //      attron(COLOR_PAIR(2)); 
         //      mvaddch(y,x,array[y-OFFSET][x-OFFSET]);
         //      attroff(COLOR_PAIR(2));
         //      break;
         //}
      }
   }
}

int Map::getTile(Location location)
{
   int mapTile = Map::array[location.second][location.first];
   switch(mapTile)
   {
      case TILE_FLOOR:
         return 46;
         break;

      case TILE_WALL:
         return 35;
         break;

      default:
         return 32;
         break;
   }
   return 0;
}

int Map::array[MAP_HEIGHT][MAP_WIDTH] =
{
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
#endif
