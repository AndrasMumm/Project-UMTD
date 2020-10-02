// TestClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Network\client.h>
#include <Game\gamestate.h>

int main()
{
	Client::GetInstance().Connect("127.0.0.1");

	GameState& gameState = GameState::getInstance();

	auto previousTickStart = 0;
	while (true)
	{
		//First things first, we process all packets
		PacketMgr::GetInstance().Process();

		auto tickStart = TIME;
		auto timePastBetweenTicks = tickStart - previousTickStart;
		if (previousTickStart == 0) timePastBetweenTicks = TICK_TIME_MS; //Can directly start

		//Check that we are not too fast
		if (timePastBetweenTicks < TICK_TIME_MS)
		{
			Sleep(TICK_TIME_MS - timePastBetweenTicks);
		}

		gameState.Update(1);
		Clock::getInstance().tick();
	}
}
