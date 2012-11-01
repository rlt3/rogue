#include "Game.h"

Game::Game()
{
   // instantiate the Render class
   Render::screen(); 

   // instantiate the animation class
   Render::animation(); 

   this->player = new Player();
   this->dungeon = new Dungeon(5);
}

void Game::handleInput(SDL_Event event)
{
   // foo
}

void Game::update()
{
   this->dungeon->update();
   this->player->draw();
}

void Game::updatePlayer(const char *state, Location direction)
{
   this->player->move(direction);
   this->player->update(state);
}

void Game::display()
{
   Render::screen()->update();
}
