#include "Game/Game.h"

int main(int argc, char* argv[]) {
   Game game;

   while(game.running)
      game.run();

   return game.quit();
}
