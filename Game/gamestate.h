#pragma once
#include "board.h"
#include "tower.h"
#include "enemy.h"
#include <vector>
#include <iostream>

using namespace std;

class GameState
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

	void update();
	void init();

	int wave;

private:
	GameState();
};
