#include "Location.h"

static int    sign(int val);
static bool   locations_intersect(struct Location p, struct Location r);
static struct Location get_area(struct Location self, int radius);
static struct Location get_area_offset(struct Location self, 
                                       int offset, 
                                       int radius);

bool location_is_same(struct Location p, struct Location r) {
  return (p.x == r.x && p.y == r.y);
}

struct Location locations_subtract(struct Location p, struct Location r) {
  struct Location location = {(p.x - r.x), (p.y - r.y)};
  return location;
}

struct Location get_direction(struct Location p, struct Location r) {
  struct Location direction;
  struct Location destination = locations_subtract(p, r);

  if(destination.x != 0) {
    direction = (struct Location){sign(destination.x), 0};
  } else {
    direction = (struct Location){0, sign(destination.y)};
  }

  return direction;
}

static struct Location get_area(struct Location self, int radius) {
  return get_area_offset(self, 0, radius);
}

static struct Location get_area_offset(struct Location self, int offset, int radius) {
  struct Location location = {
    .x = self.x + offset, 
    .y = self.y + offset,
    .w = (self.x + offset) + radius, 
    .h = (self.y + offset) + radius
  };
  return location;
}

bool locations_collide(struct Location p, struct Location r) {
  p = get_area_offset(p, 4, 12);
  r = get_area_offset(r, 4, 12);
  return locations_intersect(p, r);
}

static bool locations_intersect(struct Location p, struct Location r) {
  return ! ( p.h < r.y ||
             p.y > r.h ||
             p.w < r.x ||
             p.x > r.w );
}

static int sign(int val) {
    return (0 < val) - (val < 0);
}

