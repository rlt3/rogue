#ifndef ENTITY_H
#define ENTITY_H
#include "../Render/Render.h"
#include "../typedef/location.h"

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
