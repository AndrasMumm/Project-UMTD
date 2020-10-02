#include "gamestate.h"


GameState::GameState() : GameEntity(GAMESTATE_ENTITY_KEY) {
	Init();
}

void GameState::Update(int delta)
{
	//Calling it's own event system
	eventManager.Update(delta);

	for (Enemy* enemy : enemys)
	{
		enemy->Update(delta);
	}
}


void GameState::Init()
{
	board.loadBoardFromFile("..\\Maps\\1.map");
}
