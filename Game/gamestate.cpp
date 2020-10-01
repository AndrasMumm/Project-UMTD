#include "gamestate.h"

GameState::GameState()
{
	system("cd");
	board.loadBoardFromFile("..\\Maps\\1.map");

}

GameState::~GameState()
{
}
