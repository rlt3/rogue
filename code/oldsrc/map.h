#include <curses.h>

#define MAP_WIDTH       20
#define MAP_HEIGHT      15

#define TILE_FLOOR      0
#define TILE_WALL       1
#define TILE_GRASS      34
#define TILE_OPENDOOR   47

#define DRAGON_CHAR     71

class Map
{
   /* Extremely basic Map object.
    * It will eventually hold the tileset
    * definitions and be able to randomly
    * generate terrain/dungeons.
    */
   public:
      void draw(void);  // draw the goddamn map
      static int array[MAP_HEIGHT][MAP_WIDTH];
   private:
};

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

   void Map::draw(void)
   {
      clear();
      for (int y=1;y<=MAP_HEIGHT;y++)
         for (int x=1;x<=MAP_WIDTH;x++)
         {
            //mvaddch(y,x,array[y-1][x-1]);
            switch( array[y-1][x-1] )
            {
               case TILE_FLOOR:
                  mvaddch(y,x,46);
                  break;

               case TILE_WALL:
                  mvaddch(y,x,35);
                  break;

               default:
                  init_pair(2, COLOR_RED, COLOR_BLACK);
                  attron(COLOR_PAIR(2)); 
                  mvaddch(y,x,array[y-1][x-1]);
                  attroff(COLOR_PAIR(2));
                  break;
            }
         }
   }
