#ifndef DEARTH_LOCATION_H
#define DEARTH_LOCATION_H

#include <stdint.h>
#include <stdbool.h>

struct Location {
  int x;
  int y;
/*these can be used for direction or second points */
  int w;
  int h;
};

bool location_is_same(struct Location p, struct Location r);
bool location_collide(struct Location p, struct Location r);

struct Location locations_subtract(struct Location p, struct Location r);
struct Location get_direction(struct Location p, struct Location r);

#endif
