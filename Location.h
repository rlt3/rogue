#ifndef ROGUE_LOCATION_H
#define ROGUE_LOCATION_H

typedef struct Location {
  uint32_t  x;
  uint32_t  y;
} Location;

typedef struct Area {
  Location  a;
  Location  b;
} Area;

/*
 * Get an integer's sign value at 1: -1, 1, 0
 */
int sgn(int val) {
  return (0 < val) - (val < 0);
}

/*
 * For AI entities, we need to simulate walking somehow
 */
Location random_destination_from(Location here) {
  unsigned short int i = rand() % 5;

  int direction[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };
  int magnitude[5][2] = { {35,30}, {30,-35}, {0,0}, {-30,35}, {35,30} };

  Location destination;
  destination.x = here.x + direction[i][0]*magnitude[i][0];
  destination.y = here.y + direction[i][1]*magnitude[i][1];

  return destination;
}

/*
 * Entities do not move diagonally (because there are no
 * diagonal animations), so returning a direction that
 * has only one axis with a 0 ensure this.
 *
 * In every case, we go X first.
 */
Location get_direction_to(Location loc) {
  Location direction;

  if(loc.x != 0) {
    direction = (Location){sgn(loc.x), 0};
  } else {
    direction = (Location){0, sgn(loc.y)};
  }

  return direction;
}

bool are_same_location(Location l1, Location l2) {
  return (l1.x == l2.x && l1.y == l2.y);
}

Location subtract_locations(Location l1, Location l2) {
  Location location = { (l1.x - l2.x), (l1.y - l2.y) };
  return location;
}

Location add_locations(Location l1, Location l2) {
  Location location = { (l1.x + l2.x), (l1.y + l2.y) };
  return location;
}

/*
 * Within a 100-step radius, determine if locations
 * are nearby.
 */
bool locations_are_nearby(Location l1, Location l2) {
  Location diff = subtract_locations(l1, l2);
  return (abs(diff.x) <= 100 && abs(diff.y) <= 100);
}

bool areas_intersect(Area p, Area q) {
  return ! ( p.b.y < q.a.y || 
             p.a.y > q.b.y || 
             p.b.x < q.a.x || 
             p.a.x > q.b.x );
}

bool do_collide(Location l1, Location l2) {
  /* These points are measured from the top left
   * of each sprite. This is also where the sprite
   * is drawn from.
   *
   * Adding a fourth of the total sprite size
   * makes the `collision' box a little more
   * realistic and fluid.
   */

  Area p = {
    .a = (Location) {
           l1.x + 16,
           l1.y + 16
         },
    .b = (Location) {
           (l1.x + 16) + 32,
           (l1.y + 16) + 32
         }
  };

  Area r = {
    .a = (Location) {
           l2.x + 16,
           l2.y + 16
         },
    .b = (Location) {
           (l2.x + 16) + 32,
           (l2.y + 16) + 32
         }
  };

  return areas_intersect(p, r);
}

#endif
