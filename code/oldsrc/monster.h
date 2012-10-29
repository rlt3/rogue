#include <curses.h>

class Monster
{
   public:
      Monster();
      Monster(int health, int monsterX, int monsterY);
      void move();
      void damage();
      void attack();
      static Monster* overlay[MAP_HEIGHT][MAP_WIDTH];
      static void generate(int level);
      static void draw();
   private:
      int health;
      int monsterX, monsterY;
      int prevTile;
};

   // initliaze all values of the pointer overlay
   Monster* Monster::overlay[MAP_HEIGHT][MAP_WIDTH] = { 0 };

   Monster::Monster()
   {
      // default
      this->health=5;
      this->monsterX=18;
      this->monsterY=10;
      Monster::overlay[this->monsterY-1][this->monsterX-1]=this;
   }

   Monster::Monster(int health, int monsterX, int monsterY)
   {
      this->health=health;
      this->monsterX=monsterX;
      this->monsterY=monsterY;
      Monster::overlay[this->monsterY-1][this->monsterX-1]=this;
   }

   void Monster::generate(int level)
   {
      new Monster();
   }

   void Monster::draw()
   {
      for(int y=0;y<MAP_HEIGHT;y++)
      {
         for(int x=0;x<MAP_WIDTH;x++)
         {
            if(Monster::overlay[y][x]!=0)
            { 
               Monster* monster = Monster::overlay[y][x];
               if(monster->health>0)
                  Map::array[monster->monsterY-1][monster->monsterX-1]=DRAGON_CHAR;
               else
               {
                  Monster::overlay[monster->monsterY-1][monster->monsterX-1]=0; // remove the pointer from the overlay
                  Map::array[monster->monsterY-1][monster->monsterX-1]=0; // remove the monster from the map
                  delete monster;
               }
            }
         }
      }
   }

   void Monster::move()
   {
      Map::array[monsterY-1][monsterX-1] = prevTile;
      if(!monsterX>4 && monsterY<3)
         monsterY++;
      if(!monsterY>3 && monsterY<4)
         monsterX++;
   }

   void Monster::damage()
   {
      this->health--;
   }

   void Monster::attack()
   {
   } 
