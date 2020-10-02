#pragma once

#include"helpingHeader.h"

class Tile
{
public:
	Tile(int tileID);

	const int tileID;	
	std::vector<Tile*> neighbours;
	bool isEdge;
	int type;
	int x, y;


};

