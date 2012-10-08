#include "typedef.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"

class Game
{
   public:
      Game()
      {
         // start curses
         keypad(initscr(),1);
         curs_set(0);
         start_color(); 
         nodelay(stdscr, TRUE); // getch() is non-blocking

         this->player = new Player();
         this->map = new Map();
         this->monster = new Monster(Location (4,15));

         this->map->draw();
         this->player->draw();
         this->monster->draw();

         this->catchInput();
      }
      void moveEntities()
      {
         this->monster->move(Game::direction(this->monster));
         this->monster->draw();
         this->catchInput();
      }
      void movePlayer(Location destination)
      {
         this->player->move(destination);
         this->player->draw();
         this->catchInput();
      }
   protected:
      Player *player;
      Map *map;
      Monster *monster;
      void catchInput()
      {
         // primitively removes user input from messing up the map
         mvaddch(MAP_HEIGHT+2,0,32);
      }
      Location direction(Monster *monster)
      {
         long seed = (time((time_t*) monster));
         srand( seed ); //Randomize seed initialization
         int sign = rand() % 2; 
         int x = rand() % 2;
         if(sign==0) x=-x;

         sign = rand() % 2; 
         int y = rand() % 2;
         if(sign==0) y=-y;

         return Location (x, y); 
      }
};
