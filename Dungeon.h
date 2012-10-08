#ifndef DUNGEON_H
#define DUNGEON_H
#include "typedef.h"
#include "Monster.h"

class Dungeon
{
   public:
      int Map[MAP_HEIGHT][MAP_WIDTH]; 
      Monster* Monsters[MAP_HEIGHT][MAP_WIDTH]; 
      int floor; 

      Dungeon()
      {
         this->floor=0;
         this->Monsters[MAP_HEIGHT][MAP_WIDTH] = { NULL };

         this->generateMap();
         this->generateMonsters();
      }
      void draw(void)
      {
         clear();
         for (int y=OFFSET;y<=MAP_HEIGHT;y++)
            for (int x=OFFSET;x<=MAP_WIDTH;x++)
               mvaddch(y,x,Dungeon::getTile(Location(x-OFFSET,y-OFFSET)));
      }
      void drawEntities()
      {
         init_pair(2, COLOR_RED, COLOR_BLACK);
         attron(COLOR_PAIR(2)); 
         for(int y=OFFSET;y<MAP_HEIGHT;y++)
            for(int x=OFFSET;x<MAP_WIDTH;x++)
               if(this->Monsters[y-OFFSET][x-OFFSET]!=NULL)
                  mvaddch(location.second,location.first,103);
         attroff(COLOR_PAIR(2));
      }
      void moveEntities()
      {
         //
      }
      //void moveEntities()
      //{
      //   for (int y=OFFSET;y<=MAP_HEIGHT;y++)
      //      for (int x=OFFSET;x<=MAP_WIDTH;x++)
      //      {
      //         if(this->Monsters[x-OFFSET][y-OFFSET]!=NULL)
      //         {
      //            Monster *monster = this->Monsters[x-OFFSET][y-OFFSET];
      //            monster->move(Dungeon::direction(monster));
      //            this->Monsters[x-OFFSET][y-OFFSET]=NULL;
      //         }
      //         //mvaddch(y,x,Map::getTile(Location(x-OFFSET,y-OFFSET)));
      //      }
      //}
   protected: 
      void generateMap()
      {
         this->Map[MAP_HEIGHT][MAP_WIDTH] =
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
         this->floor++;
      }
      void generateMonsters()
      {
         // for (this->floor*3)/2 new monster at location
         // between MAP_HEIGHT and MAP_WIDTH and check
         // if location is good. Recursive check
         this->Monsters[15-OFFSET][4-OFFSET] = new Monster(Location (4,15));
         this->Monsters[12-OFFSET][6-OFFSET] = new Monster(Location (6,12));
         this->Monsters[5-OFFSET][5-OFFSET]  = new Monster(Location (5,5));
      }
      static Location direction(Monster *monster)
      {
         long seed = (time((time_t*) monster));
         srand(seed); 

         int sign = rand() % 2; 
         int x = rand() % 2;
         if(sign==0) x=-x;

         sign = rand() % 2; 
         int y = rand() % 2;
         if(sign==0) y=-y;

         return Location (x, y); 
      }
      static int getTile(Location location)
      {
         //ACS_CKBOARD - really thick checkerboard tile
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
};
#endif
