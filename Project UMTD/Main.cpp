#include <iostream>
#include <boost/asio.hpp>
#include <windows.h>
#include <Rendering/renderingMain.h>

#include "Rendering\systemclass.h"
#include "Game\gamestate.h"
#include "Game\board.h"

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{

	//Rendering Objects

	SystemClass* System;
	bool result;

	// Create the system object.
	System = new SystemClass();
	if (!System)
	{
		return 0;
	}

	//Game Objects

	GameState* gameState = new GameState();



	// Initialize and run the system object.

	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	//delete Game Objects

	delete gameState;

	return 0;
}
