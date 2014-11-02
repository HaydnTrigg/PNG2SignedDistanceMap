#include "FileHelper.h"

namespace FileHelper
{
#define F_OK    0       /* Test for existence.  */
	inline bool FileExists(const std::string& name) {
		return (_access(name.c_str(), F_OK) != -1);
	}


	template <typename genType>
	inline genType LoadfromFile(string *filename)
	{
		genType buffer;
		ifstream file(*filename, ios::in | ios::binary | ios::ate); // Create the filestream

		// : Get File Size :
		//streamsize size; [Replaced, streamsize is a __int64 definition]
		__int64 size = 0;
		// Calculate the size of the file (End-Beginning)
		if (file.seekg(0, ios::end).good()) size = file.tellg();	// Seek to the end
		if (file.seekg(0, ios::beg).good()) size -= file.tellg();	// Seek to the beginning

		if (size > 0)
		{
			buffer.resize((unsigned int)size); // Resize the buffer to accomodate the data
			file.read((char*)&buffer[0], size); // Read the file into the buffer
			file.close();
			FreeVector(file);
		}
		else buffer.clear(); // If the size was 0, clear the buffer. (Deallocate any memory of the buffer)
		return buffer;   // If the filesize was greater than 0, return the file
	}

	vector<char unsigned> LoadVectorfromFile(string *filename)
	{
		return LoadfromFile<vector<unsigned char>>(filename); // Return a Vector from the LoadFile Template
	}
}