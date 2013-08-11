#ifndef ROGUE_LOADING_HPP
#define ROGUE_LOADING_HPP

#include "Screen.hpp"

class Loading : public Screen {
public:
  bool on;

  Loading();
  void load();

private:
  SDL_Surface  *spritesheet;
};

#endif
