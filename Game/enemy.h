#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

private:
	float speed;
	float hp;
	float size;
	float armor;
	float shield;
	float regen;
	int tile;
	float progress;
};
