#ifndef COLLISION_H
#define COLLISION_H
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
      Collision() {};
      static bool at(Location &location, std::map<int, entity> &list);
};

#endif
