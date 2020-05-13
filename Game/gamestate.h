#pragma once
#include "board.h"
#include "tower.h"
#include "enemy.h"
#include "timing.h"
#include <vector>
#include <iostream>

using namespace std;

class GameState
{
public:
	GameState();
	~GameState();

	Board board;
	vector<Enemy> enemys;
	vector<Tower> towers;

	Timing time;

	void update();
	void init();

	int wave;

};