#pragma once
#include <string>
#include "helpingHeader.h"
#include <unordered_map>
#include "Tile.h"


using namespace std;

static _i64 makeKey(int x, int y) {
	_i64 ret = x;
	ret = ret << 32;
	ret += y;
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

	std::unordered_map<_i64, Tile> map;
	
	Tile* getTile(int x, int y);
	Tile* getTile(_i64 key);

	//vector<_i64> generatePath();

private:

	void createTile(int x, int y);
	
	
};
