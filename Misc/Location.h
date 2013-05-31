#ifndef LOCATION_H
#define LOCATION_H
#include <utility>
#define PAIR(x, y) std::pair<int, int>(x, y)

class Location {
   public:
      int x;
      int y;
      bool null;

      Location (int x, int y) {
         this->x = x;
         this->y = y;
         this->null = false;
      }

      Location (std::pair<int, int> coordinate) {
         this->x = coordinate.first;
         this->y = coordinate.second;
         this->null = false;
      }

      Location () {
         this->null = true;
      }

      bool empty() {
         return (this->null);
      }

      void nextLocation( const Location& destination, const Location& direction, int speed ) {
         x += (x != destination.x) ? direction.x : 0;
         y += (y != destination.y) ? direction.y : 0;
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
