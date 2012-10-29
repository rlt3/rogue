#include <curses.h>

class Player
{
   /* Very basic player object which
    * will hold more useful information
    * than just location in the future.
    *
    * Things like items and levels will
    * go here.
    */
   public:
      Player();
      void draw();                  // draw the player onto the map
      void lifebar();               // draw the life bar of the player
      void move(int z);             // move the player symbol "@"
      bool canMove(int x, int y);   // determine if the symbol can be moved
      void attack(int x, int y);
      int getHealth();
      int getFloor();
   private:
      int playerX, playerY;         // player coordinates
      int weapon;                  
      int health;
      int floor;
};

   Player::Player()
   {
      this->playerX=1;
      this->playerY=1;
      this->floor=1;
      this->weapon=0;
      this->health=20;
   }

   void Player::draw(void)
   {
      init_pair(1, COLOR_GREEN, COLOR_BLACK);
      attron(COLOR_PAIR(1)); 
      mvaddch(playerY,playerX,64);
      attroff(COLOR_PAIR(1));
   }

   void Player::lifebar(void)
   {
      mvaddch(MAP_HEIGHT+2,0,72); // H 
      mvaddch(MAP_HEIGHT+2,1,80); // P
      mvaddch(MAP_HEIGHT+2,2,58); // :
   
      // draw life bar
      for (int y=0;y<1;y++)
        for (int x=4;x<=20;x++)
        {
            init_pair(3, COLOR_WHITE, COLOR_WHITE);
            attron(COLOR_PAIR(3)); 
            mvaddch(MAP_HEIGHT+2,x,32);
            attroff(COLOR_PAIR(3));
        }

      // draw life total
      for (int y=0;y<1;y++)
        for (int x=4;x<=this->health;x++)
        {
            init_pair(4, COLOR_WHITE, COLOR_RED);
            attron(COLOR_PAIR(4)); 
            mvaddch(MAP_HEIGHT+2,x,32);
            attroff(COLOR_PAIR(4));
        }
   }

   void Player::move(int z)
   {
      if(z==0)
         if(this->canMove(this->playerX, this->playerY-1))
            playerY--;
      if(z==1)
         if(this->canMove(this->playerX+1, this->playerY))
            playerX++;
      if(z==2)
         if(this->canMove(this->playerX, this->playerY+1))
            playerY++;
      if(z==3)
         if(this->canMove(this->playerX-1, this->playerY))
            playerX--;
   }

   bool Player::canMove(int x, int y)
   {
      if(x < 1 || y < 1  || x > MAP_WIDTH || y > MAP_HEIGHT)
         return false;

      int nTileValue = Map::array[y-1][x-1];

      if(nTileValue == TILE_FLOOR || nTileValue == TILE_GRASS || nTileValue == TILE_OPENDOOR)
         return true;

      if(nTileValue == DRAGON_CHAR)
      {
         this->attack(x-1, y-1);
         return false;
      }

      return false;
   }

   int Player::getHealth()
   {
      return this->health;
   }

   int Player::getFloor()
   {
      return this->floor;
   }

   void Player::attack(int monsterX, int monsterY)
   {
      /* get weapon type:
       * 0 = fists, 1=dagger, etc.
       *
       * This number is the multiplier for determining
       * damage. So, a quick and dirty algorithm for
       * determining might be:
       *
       * damage = str+rollDice((weapon/dex))*(weapon+1));
       */
      Monster* monster = Monster::overlay[monsterY][monsterX];
      monster->damage();
      this->health=(this->health-1);
   }
