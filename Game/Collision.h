#ifndef COLLISION_H
#define COLLISION_H
#include <map>
#include <Entity/Entity.h>
#include <Misc/Location.h>

/**
 * Runs during the main game loop.
 *
 * Entities that are overlaping one another are
 * moved to the nearest possible location that
 * isn't aren't on the same grid square.
 */

class Collision {
   public:
      //static void handling(Location &location, std::map<int, Entity> &list);
      //static void handling(std::map<int, Entity> &list);
      static void handling(Entity list[]);
};

#endif
