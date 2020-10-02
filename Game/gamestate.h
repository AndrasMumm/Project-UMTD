#pragma once
#include "board.h"
#include "Entities/Tower/tower.h"
#include "Entities/Enemies/enemy.h"
#include <vector>
#include <iostream>
#include "Entities/HardcodedEntityKeys.h"

using namespace std;

class GameState : public GameEntity
{
public:
	static GameState& getInstance()
	{
		static GameState instance;

		return instance;
	}

	GameState(GameState const&) = delete;
	void operator=(GameState const&) = delete;

	Board board;
	vector<Enemy*> enemys;
	vector<Tower*> towers;

	void Update(int delta) override;
	void Init();

	int wave;

private:
	GameState();
};
