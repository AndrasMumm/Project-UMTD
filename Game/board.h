#pragma once
#include <string>
#include "helpingHeader.h"


using namespace std;



class Board
{
public:
	Board();
	~Board();
	void loadBoardFromFile(string filename);
private:

	int rows;
	int cols;

	
	vvint map; // row mayor
};
