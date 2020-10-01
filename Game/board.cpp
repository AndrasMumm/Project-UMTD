#include "board.h"
#include <fstream>
#include <string>
#include <sstream>

void Board::loadBoardFromFile(string filename) {

	ifstream infile(filename);
	string line;
	vvint vvi;
	rows = 0;
	while (getline(infile, line)) {
		cols = 0;
		istringstream iss(line);
		string symbol;
		vector<int> tmp;
		while (getline(iss, symbol, ',')) {
			tmp.push_back(atoi(symbol.c_str()));
			cols++;
		}
		rows++;
		vvi.push_back(tmp);
	}
	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {

			createTile(x, y);
			getTile(x, y)->type = vvi[y][x];
		}
	}


}

Tile* Board::getTile(int x, int y)
{
	return &map.at(makeKey(x,y));
}

Tile* Board::getTile(_i64 key)
{
	return &map.at(key);
}

void Board::createTile(int x, int y)
{
	_i64 key = makeKey(x, y);
	map.insert({ key, Tile(key)});
}

Board::Board() {}
Board::~Board() {}