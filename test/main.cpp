#include <iostream>

class Monster
{
   public:
      int weaponType;
      int location;
      Monster()
      {
         int weaponType;
         this->location=3;
      }
      void move(int direction)
      {
         this->location = this->location + direction;
         std::printf("Monster's location is %d", this->location);
      }
      static int getWeaponType()
      {
         return weaponType;
      }
};

int main()
{
   Monster monster;
   int weapon = monster.getWeaponType();
   printf("Weapon type: %d\n", weapon);
   //monster.move(1);
   return 0;
}
