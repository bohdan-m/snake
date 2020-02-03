#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <conio.h>
#include <Windows.h>

class Console
{
public:
	using FontInfo = CONSOLE_FONT_INFOEX;

	enum class Key
	{
		Enter = 13,
		Up = 72,
		Left = 75,
		Right = 77,
		Down = 80
	};

	static void Clear();
	static int GetChar();
	static FontInfo GetFontInfo();
	static void SetFontInfo(FontInfo info);
};