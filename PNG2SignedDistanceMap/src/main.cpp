#include "Engine\ApplicationEngine.h"
#include "Application\Application.h"

#define WINDOWS
#ifdef WINDOWS
#include <Windows.h>

/*
Initialises a new version of the application inside the engine.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	Application* app = (Application*)new Application();
	return Init(app, hInstance, hPrevInstance, lpCmdLine, iCmdShow);
}
#endif
