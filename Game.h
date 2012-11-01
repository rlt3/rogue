#ifndef GAME_H
#define GAME_H
#include "Render/Render.h"
#include "Entity/Player.h"
#include "Dungeon/Dungeon.h"

class Game
{
   public:
      Game();

      // handle player input
      void handleInput(SDL_Event event);

      // update entities (animation states, position, etc)
      void update();

      void updatePlayer(const char *state, Location direction);
      
      // display these updates
      void display();

   protected:
      Player *player;
      Dungeon *dungeon;

   private:
      bool state; // states of the game (on or off)
};

#endif
