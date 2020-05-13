#include <iostream>
#include <windows.h>
#include <Rendering/renderingMain.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	RenderingMain(hInstance, hPrevInstance, pScmdline, iCmdshow);
}