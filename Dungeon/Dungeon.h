#ifndef DUNGEON_H
#define DUNGEON_H

#define MAP_HEIGHT     20
#define MAP_WIDTH      20
#define TILE_FLOOR     '.'
#define TILE_WALL      '#'
#define TILE_DOOR      '/'
#define TILE_OPENDOOR  '|'

/**
 * This class controls the Dungeon and all the 
 * things that reside inside. So, it creates all
 * of the Entities and items that may be found.
 *
 * Using a linked list of all the monsters, the
 * dungeon can go through and update each one
 * as it needs to.
 *
 * Right now, since we're testing, we do not have
 * a linked list but just monster pointer and we 
 * will do things with just that.
 */

class Dungeon
{
   public:
      Dungeon(int difficulty);
      void update();

      char map[MAP_HEIGHT][MAP_WIDTH];

   protected:
      void generate();
};
#endif
