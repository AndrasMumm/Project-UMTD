// TestClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Network\client.h>

int main()
{
	Client::GetInstance().Connect("127.0.0.1");

	while (true)
	{
		Sleep(1000);
	}
}
