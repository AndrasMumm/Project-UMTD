#include "gamestate.h"


GameState::GameState() {
	init();
	update();
}

void GameState::update()
{
}

void GameState::init()
{
	system("cd");
	board.loadBoardFromFile("..\\Maps\\1.map");
}
