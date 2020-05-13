#include <iostream>
#include <windows.h>
#include <Rendering/renderingMain.h>

#include "Rendering\systemclass.h"

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

int WINAPI RenderingMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	// Create the system object.
	System = new SystemClass();
	if (!System)
	{
		return 0;
	}

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

	return 0;
}
