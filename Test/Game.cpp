#include "Game.h"

Game *Game::s_instance = nullptr;

Game * Game::get()
{
	if (!s_instance)
		s_instance = new Game();
	return s_instance;
}
