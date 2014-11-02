#include "stdafx.h"

#undef SetConsoleTitle
#undef SetWindowTitle

#pragma once
class WindowObject
{
public:
	// :: Constructors ::
	WindowObject();
	~WindowObject();

	// :: Methods ::
	void Init(HINSTANCE hinstance, WNDPROC wndproc);

#ifdef _CONSOLE
	void CreateConsole();
	void SetConsoleTitle(string text);
#endif

	// :: Variables ::
	// : Window/Viewport :
	WNDCLASS	WC;			// WinAPI Windows Class
	// WinAPI Window Handle
	HWND		hWnd;
	MSG			msg;		// WinAPI Message

	// : Rendering :
	HINSTANCE	hInst;// Hardware Instance
};

