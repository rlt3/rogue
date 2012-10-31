#ifndef DUNGEON_H
#define DUNGEON_H
#include "../typedef/location.h"
#include "../Render/Render.h"
#include "../Entity/Entity.h"

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
      Dungeon(int level);
      void draw();
      void update();
      void generate();
   protected:
      Entity *monster;
      int level;
};
#endif
