#pragma once

#include"helpingHeader.h"

class Tile
{
public:
	Tile(long tileID);

	const long tileID;	
	std::vector<Tile*> neighbours;
	bool isEdge;
	int type;


};

