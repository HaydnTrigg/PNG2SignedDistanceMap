#ifdef _CONSOLE
#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdafx.h"

#pragma once
namespace Console
{
	namespace Colors
	{
		enum ConsoleColor
		{
			CMD_BLACKMAJOR = 0x00,
			CMD_BLACKMINOR = 0x00,
			CMD_BLUEMAJOR = 0x10,
			CMD_BLUEMINOR = 0x01,
			CMD_GREENMAJOR = 0x20,
			CMD_GREENMINOR = 0x02,
			CMD_AQUAMAJOR = 0x30,
			CMD_AQUAMINOR = 0x03,
			CMD_REDMAJOR = 0x40,
			CMD_REDMINOR = 0x04,
			CMD_PURPLEMAJOR = 0x50,
			CMD_PURPLEMINOR = 0x05,
			CMD_YELLOWMAJOR = 0x60,
			CMD_YELLOWMINOR = 0x06,
			CMD_LIGHTGREYMAJOR = 0x70,
			CMD_LIGHTGREYMINOR = 0x07,
			CMD_GRAYMAJOR = 0x80,
			CMD_GRAYMINOR = 0x08,
			CMD_LIGHTBLUEMAJOR = 0x90,
			CMD_LIGHTBLUEMINOR = 0x09,
			CMD_LIGHTGREENMAJOR = 0xA0,
			CMD_LIGHTGREENMINOR = 0x0A,
			CMD_LIGHTAQUAMAJOR = 0xB0,
			CMD_LIGHTAQUAMINOR = 0x0B,
			CMD_LIGHTREDMAJOR = 0xC0,
			CMD_LIGHTREDMINOR = 0x0C,
			CMD_LIGHTPURPLEMAJOR = 0xD0,
			CMD_LIGHTPURPLEMINOR = 0x0D,
			CMD_LIGHTYELLOWMAJOR = 0xE0,
			CMD_LIGHTYELLOWMINOR = 0x0E,
			CMD_WHITEMAJOR = 0xF0,
			CMD_WHITEMINOR = 0x0F
		};

		const ConsoleColor Error = CMD_LIGHTREDMINOR;
		const ConsoleColor Success = CMD_GREENMINOR;
		const ConsoleColor Text = CMD_LIGHTGREYMINOR;
	}
	

	static struct Out {
		Out & operator<<(const Colors::ConsoleColor &token) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, token);
			return *this;
		}

		// : String :
		Out & operator<< (const std::string &token) {
			printf(token.c_str());
			OutputDebugString(token.c_str());
			*this << Colors::CMD_LIGHTGREYMINOR;
			return *this;
		}

		// : Numerical Types : "Convert numbers to string, convert string to characters, print"


		Out & operator<< (const unsigned __int32 &token) { return *this << std::to_string(token); }
		Out & operator<< (const __int32 &token) { return *this << std::to_string(token); }
		Out & operator<< (const unsigned __int16 &token) { return *this << std::to_string(token); }
		Out & operator<< (const __int16 &token) { return *this << std::to_string(token); }
		Out & operator<< (const unsigned __int8 &token) { return *this << std::to_string(token); }
		Out & operator<< (const __int8 &token) { return *this << std::to_string(token); }
		Out & operator<< (const unsigned __int64 &token) { return *this << std::to_string(token); }
		Out & operator<< (const __int64 &token) { return *this << std::to_string(token); }
		Out & operator<< (const float &token) { return *this << std::to_string(token); }
		Out & operator<< (const double &token) { return *this << std::to_string(token); }

	} Out;

	// Generic Template for Printing with a Line
	static struct OutLn {
		OutLn & operator<<(const Colors::ConsoleColor &token) {
			Out << token;
			return *this;
		}
		template<typename _Ty>
		OutLn & operator<< (const _Ty &token) {
			Out << token << "\n";
			return *this;
		}
	} OutLn;

	static void Clear()
	{
		system("cls");
	}

}
#endif
#endif