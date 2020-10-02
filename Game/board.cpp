#include "board.h"
#include <fstream>
#include <string>
#include <sstream>

void Board::loadBoardFromFile(string filename) {

	ifstream infile(filename);
	string line;
	vvint vvi;
	height = 0;
	while (getline(infile, line)) {
		width = 0;
		istringstream iss(line);
		string symbol;
		vector<int> tmp;
		while (getline(iss, symbol, ',')) {
			tmp.push_back(atoi(symbol.c_str()));
			width++;
		}
		height++;
		vvi.push_back(tmp);
	}
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			createTile(x, y);
			Tile* t = getTile(x, y);
			t->type = vvi[y][x];
			t->x = x;
			t->y = y;
		}
	}
	connectNeighbours();
	
	
}

Tile* Board::getTile(short x, short y)
{
	return &map.at(makeKey(x,y));
}

Tile* Board::getTile(int key)
{
	return &map.at(key);
}

void Board::connectNeighbours()
{
	for (auto i = map.begin(); i != map.end(); i++) {
	
		Tile* c = &i->second;
		if (c->x > 0)c->neighbours.push_back(getTile(c->x - 1, c->y));
		if (c->x < width-1)c->neighbours.push_back(getTile(c->x + 1, c->y));
		if (c->y > 0)c->neighbours.push_back(getTile(c->x, c->y-1));
		if (c->y < height-1)c->neighbours.push_back(getTile(c->x, c->y+1));
	}
}

vector<vector<int>> Board::generatePath()
{
	vector<vector<int>> ret;

	Tile* start = 0;
	Tile* end = 0;
	for (auto i = map.begin(); i != map.end(); i++) {
		if (i->second.type == 1) start = &(i->second);
		if (i->second.type == 2) end = &(i->second);
	}

	if (start == 0 || end == 0) return ret;
	Tile* current = start;
	Tile* last = start;
	vector<int> tmp;
	tmp.push_back(start->tileID);
	while (current != end) {
		for (Tile* t : current->neighbours) {
			if (t->type == 3 && t != last) {
				tmp.push_back(t->tileID);
				last = current;
				current = t;
				break;
			}
			if (t->type == 2) {
				tmp.push_back(end->tileID);
				current = t;
				break;
			}
			
		}

	}
	ret.push_back(tmp);


	return ret;

}

void Board::createTile(short x, short y)
{
	int key = makeKey(x, y);
	map.insert({ key, Tile(key)});
}

Board::Board() {}
Board::~Board() {}