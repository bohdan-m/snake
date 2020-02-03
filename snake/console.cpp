#include "console.h"

void Console::Clear()
{
	system("cls");
}

int Console::GetChar()
{
	return _getch();
}

Console::FontInfo Console::GetFontInfo()
{
	Console::FontInfo console_info;
	console_info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE c_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(c_handle, false, &console_info);

	return console_info;
}

void Console::SetFontInfo(Console::FontInfo info)
{
	HANDLE c_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCurrentConsoleFontEx(c_handle, false, &info);
}