#include "board.h"
#include <fstream>
#include <string>
#include <sstream>

void Board::loadBoardFromFile(string filename) {

	ifstream infile(filename);
	string line;
	
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
		map.push_back(tmp);
	}
}

Board::Board() {}
Board::~Board() {}