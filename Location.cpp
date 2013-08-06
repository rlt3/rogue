#include "Location.hpp"

/*
 * Start definitions for class Location
 */

Location::Location() {
  this->x = 0;
  this->y = 0;
}

Location::Location(int x, int y) {
  this->x = x;
  this->y = y;
}

Location Location::new_destination() {
  unsigned short int i = rand() % 5;

  int direction[5][2] = { {0,1}, {-1,0}, {0,0}, {1,0}, {0,-1} };
  int magnitude[5][2] = { {35,30}, {30,-35}, {0,0}, {-30,35}, {35,30} };

  Location destination;
  destination.x = this->x + direction[i][0]*magnitude[i][0];
  destination.y = this->y + direction[i][1]*magnitude[i][1];

  return destination;
}

Location Location::get_direction_to() {
  Location direction;

  if(this->x != 0) {
    direction = Location(sign(this->x), 0);
  } else {
    direction = Location(0, sign(this->y));
  }

  return direction;
}

bool Location::is_same(Location other) {
  return (this->x == other.x && this->y == other.y);
}

bool Location::is_nearby(Location other) {
  Location diff = Location::subtract(*this, other);
  return (abs(diff.x) <= 100 && abs(diff.y) <= 100);
}

/* static */
Location Location::subtract(Location l1, Location l2) {
  Location location((l1.x - l2.x), (l1.y - l2.y));
  return location;
}

/* static */
Location Location::add(Location l1, Location l2) {
  Location location((l1.x + l2.x), (l1.y + l2.y));
  return location;
}

/* static */
int Location::sign(int val) {
  return (0 < val) - (val < 0);
}

/*
 * Start definitions for class Area
 */

bool Area::intersects(Area other) {
  return ! ( this->p2.y < other.p1.y || 
             this->p1.y > other.p2.y || 
             this->p2.x < other.p1.x || 
             this->p1.x > other.p2.x );
}

bool Area::collides_with(Location other) {
  Area p(Location(this->p1.x + 16, this->p1.y + 16),
         Location((this->p1.x + 16) + 32, (this->p1.y + 16) + 32));

  Area r(Location(other.x + 16, other.y + 16),
         Location((other.x + 16) + 32, (other.y + 16) + 32));

  return p.intersects(r);
}