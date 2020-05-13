#pragma once
#include <string>

using namespace std;



class Board
{
public:
	Board();
	~Board();

private:
	void loadBoardFromFile(string filename);
};
