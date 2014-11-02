#include "Application.h"
#include "../Libraries/picopng/picopng.h"
#include "../Libraries/triggmath/triggmath.h"
#include "../Engine/FileHelper.h"

#include "../Engine/WindowObject.h"

Application::Application()
{
}

Application::~Application()
{
	delete Window;
}

void Application::Init()
{
	Window = new WindowObject();
	Window->CreateConsole();
	Window->SetConsoleTitle("PNG2SignedDistanceMap");

	// Welcome Message
	Console::Out << (Console::Colors::ConsoleColor)(Console::Colors::CMD_LIGHTBLUEMAJOR + Console::Colors::CMD_WHITEMINOR) <<
		"PNG2SignedDistanceMap v1.0.2 written by Haydn Trigg\n" << Console::Colors::Text <<
		"Please input filename: ";

	// :: Source File ::
	string filename;
	bool file_exists = false;
	std::cin >> filename;
	while (!file_exists)
	{
		if (filename == "q") exit(0);
		else file_exists = FileHelper::FileExists(filename);
		if (file_exists) Console::Out << Console::Colors::Success << "PNG File Exists! " << "[" << filename << "]\n";
		else
		{
			Console::Out << Console::Colors::Error << "PNG Does Not Exist! Please try again...\n" << "Please input filename: ";
			std::cin >> filename;
		}
	}

	// :: Kernel Size ::
	Console::Out << "Input Kernel Size: ";
	int kernel_size = 0;
	string kernel_string;

	while (kernel_size <= 0)
	{
		std::cin >> kernel_string;
		if (kernel_string == "q") exit(0);
		else
		{
			try
			{
				kernel_size = atoi(kernel_string.c_str());
			}
			catch (void*)
			{
				Console::OutLn << Console::Colors::Error << "Please input a number!";
				kernel_size = 0;
			}
		}

		if (kernel_size > 0)
		{
			Console::Out << Console::Colors::Success << "Kernel Size " << "[" << kernel_size << "]\n";
			break;
		}
		else Console::Out << Console::Colors::Error << "Kernel Size must be greater than zero!\n" << "Please input Kernel Size: ";
	}

	// :: Output File ::
	string out_filename;
	bool out_filename_created = false;
	while (!out_filename_created)
	{
		Console::Out << "Output Filename: ";
		std::cin >> out_filename;
		if (filename == "q") exit(0);
		else file_exists = FileHelper::FileExists(out_filename);

		if (file_exists)
		{
			Console::Out << Console::Colors::Text << "File Exists! Overwrite [Y/N]" << "[" << filename << "]\n";
			string answer;
			std::cin >> answer;
			out_filename_created = (answer == "Y" || answer == "y");
		}
		else out_filename_created = true;
	}
	Console::Out << Console::Colors::Success << "File Output Name:" << "[" << out_filename << "]\n";

	unsigned long long start_time = GetTickCount64();

	picopng::PNG png(filename);
	float searchDistance = (float)kernel_size;

	if (png.Width > 0 && png.Height > 0 && png.Data.size() > 0) // Ensure PNG file is ok
	{
		size_t png_data_size = png.Data.size();

		// Create an array to store the pixel distance data
		std::vector<float> distance_data;
		distance_data.resize(png_data_size / 4);

		// Log the initial progress.
		string str_out = string("Completed: ") + std::to_string(0) + "/" + std::to_string(png.Width) + "\n";
		Console::Out << str_out;

		// Record start time
		unsigned long long last_time = GetTickCount64();

		// Loop Variables
		float delta = 0;
		unsigned char data = 0;
		float init = (float)sqrt((double)(png.Width*png.Width + png.Height*png.Height)); // Maximum possible distance
		float max = 0.0f;
		const float min = 0.0f;

		for (unsigned int i = 0; i < png.Width; i++) //0
		{
			for (unsigned int j = 0; j < png.Height; j++) //1
			{
				float *output = &distance_data[i + j * png.Width];
				*output = init;
				data = png.Data[4 * (i + j * png.Width)]; // Get the Data

				if (data <= 0) // Ensure the pixel isn't going to be of distance 0
				{
					for (unsigned int k = 0; k < png.Width; k++) //2
					{
						for (unsigned int w = 0; w < png.Height; w++) //3
						{
							data = png.Data[4 * (k + w * png.Width)]; // Get the Data
							if (data > 0)
							{
								// Calculate distance and maintain maximum precision
								// Calculate the distance squared
								// NOTE: Leave as distance squared and use square root later to improve performance.
								long long x_dist = (long long)i - k;
								long long y_dist = (long long)j - w;
								float distance = (float)(x_dist*x_dist + y_dist*y_dist);

								if (distance < *output) *output = distance;
								if (distance > max) max = distance;
								//if (distance < min) min = distance;

								if (*output <= 1) break;;
							}
						}
						if (*output <= 1) break;;
					}
				}
				else *output = 0;
			}

			// :: Calculate the remaning time and log progress to console ::
			{
				unsigned long long current_time = GetTickCount64();
				unsigned long long delta_time = current_time - last_time;
				last_time = current_time;
				float f_delta_time = (float)((double)delta_time / 1000);
				float more_ticks = (float)(png.Width - i);
				if (i == 0) delta = f_delta_time;
				delta = (delta * 2 + f_delta_time) / 3.0f;
				float remaning_time = delta * more_ticks;

				str_out = string("Completed: ") + std::to_string(i + 1) + "/" + std::to_string(png.Width) + " Remaning: " + std::to_string(remaning_time) + "s\n";
				Console::Out << str_out;
			}
		}

		FileHelper::FreeVector(png.Data); // Free the PNG Source Data. It will no longer be used.

		// : Convert data into 0-1 byte data :
		std::vector<unsigned char> texture_data;
		texture_data.resize(png_data_size / 4);

		for (unsigned int i = 0; i < png.Width; i++) for (unsigned int j = 0; j < png.Height; j++)
		{
			float value = sqrtf(distance_data[i + j*png.Width]);

			// Clamp distance to -/+ 
			value = Math::Clamp(value, -searchDistance, +searchDistance);

			// Convert from -search,+search to 0,+search*2 and then convert to 0.0, 1.0 and invert
			value = 1.0f - Math::Clamp((value + searchDistance) / (searchDistance + searchDistance), 0, 1);

			texture_data[i + (png.Height - j - 1)*png.Width] = (unsigned char)(value*255.0f);
		}

		FileHelper::FreeVector(distance_data); // Free the Distance Data. It will no longer be used.

		// : Create Minochrome Bitmap Pixel Data
		std::vector<Pixel> bmp_data;
		bmp_data.resize(texture_data.size());
		for (unsigned int i = 0; i < png.Width; i++) for (unsigned int j = 0; j < png.Height; j++)
		{
			unsigned char data = texture_data[i + j*png.Width];
			bmp_data[i + j*png.Width].r = data;
			bmp_data[i + j*png.Width].g = data;
			bmp_data[i + j*png.Width].b = data;
		}

		FileHelper::FreeVector(texture_data); // Free the Texture Data. It will no longer be used.

		// Try and save the Bitmap and log the result.
		if (SaveBMP((unsigned char*)(&bmp_data[0]), bmp_data.size() * 3, png.Width, png.Height, (char*)out_filename.c_str()))
		{
			// Process completed sucessfully. Calculate time and display to console.
			unsigned long long time = GetTickCount64() - start_time;
			float ftime = (float)((double)time / 1000);
			Console::Out << Console::Colors::Success << "Process Complete: t["<< ftime <<"]" << "Saved to " << "[" << out_filename << "]\n";
		}
		// Something went wrong while trying to save the Bitmap File. Display an error message.
		else Console::Out << Console::Colors::Error << "Process Failed: " << "Could not save output bitmap file!\n";

		FileHelper::FreeVector(bmp_data); // Free the bitmap data so the application can idle with minimum memory usage.

	}
	// Something went wrong while trying to load the PNG File. Display an error message.
	else Console::Out << Console::Colors::Error << "Process Failed: " << "Bad PNG import!\n";

	system("pause"); // Wait for the user to exit the application.
}

bool Application::SaveBMP(unsigned char* data, DWORD data_size, int width, int height, char* filepath)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;
	memset(&bmfh, 0, sizeof (BITMAPFILEHEADER));
	memset(&info, 0, sizeof (BITMAPINFOHEADER));

	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+data_size;
	bmfh.bfOffBits = 0x36;

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0x0ec4;
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	HANDLE file = CreateFile(filepath, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (NULL == file)
	{
		CloseHandle(file);
		return false;
	}

	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof (BITMAPFILEHEADER),
		&bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	if (WriteFile(file, &info, sizeof (BITMAPINFOHEADER),
		&bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	if (WriteFile(file, data, data_size, &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	CloseHandle(file);
	return true;
}