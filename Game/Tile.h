#pragma once

#include"helpingHeader.h"

class Tile
{
public:
	Tile(_i64 tileID);

	const _i64 tileID;	
	std::vector<Tile*> neighbours;
	bool isEdge;
	int type;
	int x, y;


};

