#ifndef GAME_H
#define GAME_H
#include "typedef.h"
#include "Player.h"
#include "Dungeon.h"
#include "Monster.h"
//#include "Map.h"

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
         this->dungeon = new Dungeon();
         //this->monster = new Monster(Location (4,15));

         this->map->draw();
         this->player->draw();
         this->dungeon->draw();

         this->catchInput();
      }
      void moveEntities()
      {
         this->dungeon->moveEntities();
         this->dungeon->drawEntities();
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
      Dugeon *dungeon;
      //Monster *monster;
      void catchInput()
      {
         // primitively removes user input from messing up the map
         mvaddch(MAP_HEIGHT+2,0,32);
      }
};
#endif
