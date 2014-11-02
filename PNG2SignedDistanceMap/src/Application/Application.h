#include "../Engine/stdafx.h"

class WindowObject;

#pragma once
class Application
{
public:
	// :: Type Definitions ::
	struct Pixel{ unsigned char r, g, b; };

	// :: Constructors ::
	Application();
	virtual ~Application();

	// :: Variables ::
	WindowObject *Window;

	// :: Methods ::
	virtual void Init();
	bool SaveBMP(unsigned char* data, DWORD data_size, int width, int height, char* filepath);
};

