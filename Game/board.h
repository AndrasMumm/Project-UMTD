#pragma once
#include <string>
#include "helpingHeader.h"
#include <unordered_map>
#include "Tile.h"
using namespace std;

long makeKey(int x, int y) {
	long ret = x << 32 + y;
	return ret;
}


class Board
{
public:
	Board();
	~Board();
	void loadBoardFromFile(string filename);

	int rows;
	int cols;

	std::unordered_map<long, Tile> map;

	Tile* getTile(int x, int y);
	Tile* getTile(long key);

private:

	void createTile(int x, int y);
	
	
};
