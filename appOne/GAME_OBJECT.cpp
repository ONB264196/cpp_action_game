#include "GAME.h"
#include "GAME_OBJECT.h"

GAME_OBJECT::GAME_OBJECT(GAME* game)
{
	Game = game;
}

GAME_OBJECT::~GAME_OBJECT()
{
	Game = nullptr;
}
