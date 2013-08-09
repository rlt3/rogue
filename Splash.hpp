#ifndef ROGUE_SPLASH_HPP
#define ROGUE_SPLASH_HPP

#include "Game.hpp"

class Splash : public Game {
public:
  bool on;
  Splash(const char* splash);
  void splash_loop();

protected:
  SDL_Surface  *spritesheet;

};

#endif
