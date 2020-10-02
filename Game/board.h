#pragma once
#include <string>
#include "helpingHeader.h"
#include <unordered_map>
#include "Tile.h"


using namespace std;

static int makeKey(short x, short y) {
	int ret = x;
	ret = ret << 16;
	ret += y;
	return ret;
}


class Board
{
public:
	Board();
	~Board();
	void loadBoardFromFile(string filename);

	int height;
	int width;

	std::unordered_map<int, Tile> map;
	
	Tile* getTile(short x, short y);
	Tile* getTile(int key);

	void connectNeighbours();
	vector<vector<int>> generatePath();

private:

	void createTile(short x, short y);
	
	
};
