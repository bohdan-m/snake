#include "ui.h"

namespace ui {
	Menu::Menu(std::string title) : title(title) { }

	void Menu::AddMenuItem(MenuItem item)
	{
		items.push_back(item);
	}

	void Menu::Show()
	{

	}

	void Menu::Hide()
	{

	}


	void Console::Clear()
	{
		system("cls");
	}

	int Console::GetChar()
	{
		return _getch();
	}

};