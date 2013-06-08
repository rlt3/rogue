#ifndef COLLISION_H
#define COLLISION_H
#include <Game/Game.h>

// extends Game to access it's methods
// singleton method for global access?
//
// override constructor/destructor as
// not to call Game() constructor and 
// basically reload SDL twice

class Collision : public Game {
   public:
      Collision() {};
      static bool at(Location &location);
};

#endif
