#ifndef LOCATION_H
#define LOCATION_H
#include <utility>
#define PAIR(x, y) std::pair<int, int>(x, y)

/* Get sign of a value represented as -1, 1, or 0 */
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class Location {
   public:
      int x;
      int y;

      Location (int x, int y) {
         this->x = x;
         this->y = y;
      }

      Location (std::pair<int, int> coordinate) {
         this->x = coordinate.first;
         this->y = coordinate.second;
      }

      Location () {
         //
      }

      bool nearby(const Location& location, int radius) {
         Location diff = *this - location;
         return (abs(diff.x) <= radius && abs(diff.y) <= radius);
      }

      //bool reached(const Location& location) {
      //   return (*this == location);
      //}

      Location world() {
         return Location( ((x+(32/2))/32), ((y+(32/2))/32) );
      }

      void step( const Location& destination, const Location& direction, int speed ) {
         //x += (x != destination.x) ? direction.x*(speed/(speed/2)) : 0;
         //y += (y != destination.y) ? direction.y*(speed/(speed/2)) : 0;
         
         x += (x != destination.x) ? direction.x*1 : 0;
         y += (y != destination.y) ? direction.y*1 : 0;
      }

      bool operator ==(const Location &other ) {
         return (x == other.x && y == other.y);
      }

      bool operator !=(const Location &other ) {
         return !(*this == other);
      }

      friend Location operator+(const Location &l1, const Location &l2) {
          return Location( (l1.x + l2.x), (l1.y + l2.y) );
      }

      friend Location operator-(const Location &l1, const Location &l2) {
          return Location( (l1.x - l2.x), (l1.y - l2.y) );
      }

      friend Location operator*(const Location &l1, const Location &l2) {
          return Location( (l1.x * l2.x), (l1.y * l2.y) );
      }
};

#endif
