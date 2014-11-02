#include "stdafx.h"

#pragma once
namespace FileHelper
{
	template <typename genType>
	extern inline genType LoadfromFile(string *filename);

	extern vector<unsigned char> LoadVectorfromFile(string *filename);
	extern __int64 	GetFileSize(string path);
	extern inline bool FileExists(const std::string& name);

	template<typename _Ty>
	void FreeVector(_Ty & vector)
	{
		_Ty temp_vector;
		vector.swap(temp_vector);
	}
	
	template<typename _Ty>
	void FreeVector(_Ty * vector)
	{
		_Ty temp_vector;
		vector->swap(temp_vector);
	}
}

