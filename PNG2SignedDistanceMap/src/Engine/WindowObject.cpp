#include "WindowObject.h"

WindowObject::WindowObject()
{
}


WindowObject::~WindowObject()
{
}

/*
Initializes the window object and the "Window Context" using WINAPI+
*/
void WindowObject::Init(HINSTANCE hinstance, WNDPROC wndproc)
{
	CreateConsole();
}

/*
Assignes the window title text of all consoles attached to the process
*/
void WindowObject::SetConsoleTitle(string text)
{
	SetConsoleTitleA(text.c_str());
}

/*
Allocates a console process to the application process
*/
void WindowObject::CreateConsole()
{
	// Create the Console
	AllocConsole();

	// Create Console Output Handle
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	// Create Console Input Handle
	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	// Get the Console Window Handle
	hWnd = GetConsoleWindow();

	SetConsoleTitle("Console");
}