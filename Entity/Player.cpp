#include "Player.h"

Player::Player() : Entity("player")
{
   this->location = std::make_pair(250,250);
}
