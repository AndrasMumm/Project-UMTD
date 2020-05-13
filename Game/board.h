#pragma once
#include <string>
#include "helpingHeader.h"


using namespace std;



class Board
{
public:
	Board();
	~Board();

private:

	int rows;
	int cols;

	void loadBoardFromFile(string filename);
	vvint map; // row mayor
};
