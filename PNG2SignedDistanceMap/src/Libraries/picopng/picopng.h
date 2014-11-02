#ifndef PICOPNG_H
#define PICOPNG_H

#include "../../Engine/stdafx.h"

namespace picopng
{

// :: PNG ::
class PNG
{
public:
	// :: Constructors ::
	PNG(string* path);
	PNG(string path);

	// :: Variables ::
	unsigned __int32 Width, Height;
	vector<unsigned char> Data;
	string FilePath;
private:
	// :: Private Methods ::
	void LoadPNG(string* path);

};

int DecodePNG(PNG& out_png, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32);
PNG LoadPNG(string path);

}

#endif