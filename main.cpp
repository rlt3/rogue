#include "Game.h"

int main(int argc, char* argv[]) {
   Game game;

   while(game.running)
      game.run();

   game.quit();
   return 0;
}
