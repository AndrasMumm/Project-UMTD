// TestServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Network\server.h>
#include <Game\gamestate.h>
#include <Game\Entities\Enemies\EnemyFactory.h>
#include <Game\Entities\Enemies\EnemyTypeID.h>

int main()
{
	Server::GetInstance().Start(1234);

	GameState& gameState = GameState::getInstance();

	auto startTime = TIME;
	auto lastEnemySpawnedTick = 0;
	auto previousTickStart = 0;
	while (true)
	{
		//First things first, we process all packets
		PacketMgr::GetInstance().Process();

		auto tickStart = TIME;
		auto timePastBetweenTicks = tickStart - previousTickStart;
		if (previousTickStart == 0) {
			timePastBetweenTicks = TICK_TIME_MS;
		}//Can directly start

		//Check that we are not too fast
		if (timePastBetweenTicks < TICK_TIME_MS)
		{
			auto timeToSleep = TICK_TIME_MS - timePastBetweenTicks - 1;
			Sleep(timeToSleep);
			timePastBetweenTicks = TIME - previousTickStart;
		}

		previousTickStart = TIME;

		std::cout << "Time since last pulse: " << timePastBetweenTicks << std::endl;

		if (TICK - lastEnemySpawnedTick >= 3 && TIME - startTime > 5000)
		{
			EnemyFactory::SpawnNewEnemy(ENEMY_TYPE_DEFAULT, 1, 0, 0, TICK + 5);
			std::cout << "Queued spawn enemy event " << std::endl;
			lastEnemySpawnedTick = TICK;
		}

		gameState.Update(1);
		Clock::getInstance().tick();
	}
}
