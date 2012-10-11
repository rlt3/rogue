#include "Game.h"

Game::Game()
{
   Render::init();
}

Game::~Game()
{
   // foo
}

void Game::handleInput(SDL_Event event)
{
   // foo
}

void Game::update()
{
   // dungeon update
}

void Game::display()
{
   Render::game();
}
