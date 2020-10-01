#pragma once

class GameEvent
{
public:
	int triggerTick;

	GameEvent() = default;
	virtual ~GameEvent() = 0;
	virtual void trigger(GameEntity* entity, int deltaTickDifference = 0) = 0;
	virtual void onCreate(GameEntity* entity) = 0;

};
