#ifndef GAME_H
#define GAME_H
#include "Render.h"

class Game
{
   public:
      Game();
      ~Game();

      // handle player input
      void handleInput(SDL_Event event);

      // update entities (animation states, position, etc)
      void update();
      
      // display these updates
      void display();

   private:
      bool state; // states of the game (on or off)

      //Dungeon *dungeon;
};
#endif
