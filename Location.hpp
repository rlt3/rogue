#ifndef ROGUE_LOCATION_HPP
#define ROGUE_LOCATION_HPP

#include <cstdlib>

class Location {
public:
  int x;
  int y;

  Location();
  Location(int x, int y);

  Location new_destination();
  Location get_direction_to();

  bool is_same(Location other);
  bool is_nearby(Location other);

  static Location subtract(Location l1, Location l2);
  static Location add(Location l1, Location l2);
  static int sign(int value);
};

class Area {
public:
  Location p1;
  Location p2;

  Area();
  Area(Location p1, Location p2);

  bool intersects(Area other);
  bool collides_with(Location other);
};

#endif
