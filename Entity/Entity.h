#ifndef ENTITY_H
#define ENTITY_H
#include <utility>
#include "../Render/Animation.h"
#include "../Render/Render.h"

typedef std::pair<int, int> Location; // coordinate pair (x,y)

class Entity
{
   public:
      Entity(const char *type);
      void draw();
      void update(const char *state);
      Location location;
      const char *type;
   protected:
      const char *state;
};
#endif
