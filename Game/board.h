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

	vvint map; // row mayor

	int rows;
	int cols;

private:


	
	
};
