#include "SystemHeader.h"

class Application;
class Window;

#ifdef WINDOWS
	// : Methods :
	extern int Init(Application* application, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow);
	extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif
