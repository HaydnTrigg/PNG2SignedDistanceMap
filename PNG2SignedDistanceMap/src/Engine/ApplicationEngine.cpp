#include "ApplicationEngine.h"
#include "../Application/Application.h"
#include "stdafx.h"

Application* application;

#ifdef WINDOWS

int Init(Application* app, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	application = app;

	union
	{
		unsigned __int32 i;
		char c[4];
	} _i = { 0x01020304 };
	bool b_IsLittleEndian = (_i.c[0] == 1);

	// Process Command Line Options
	TCHAR cmdline[4096];
	TCHAR* argv[4096];
	int argc = 0;
	strcpy_s(cmdline, GetCommandLine());
	char* Pos = 0;
	argv[argc] = _tcstok_s(cmdline, TEXT(" \t"), &Pos);
	while (argv[argc] != 0)
	{
		argc++;
		argv[argc] = _tcstok_s(0, TEXT(" \t"), &Pos);
	}

	app->Init();

	return 0; // No Errors
}

#endif