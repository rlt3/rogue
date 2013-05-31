#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <time.h>

#include "../Render/Render.h"
#include "../Dungeon/Dungeon.h"
#include "../Entity/Player.h"
#include "../Entity/Monster.h"

const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 60 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 10;

class Game
{
   public:
      Game();
      ~Game();
      void run();

      void update();
      void updatePlayer(int state, Location direction);
      void interpolation();
      void display();
      void quit();

      bool running; // states of the game (on or off)

   protected:
      Render render;
      //Dungeon dungeon;
      Player player;
      Monster monster;
      Monster baddie;

      void handleInput(SDL_Event event);
      void drawDungeon();
   
   private:
      SDL_Event event;
      int loops;
      long double t;
      static const double dt = 1.0 / 30.0;
};

#endif
