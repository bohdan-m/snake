#include "ui.h"

namespace ui {
	Menu::Menu(std::string title) : title(title) { }

	void Menu::AddMenuItem(MenuItem item)
	{
		items.push_back(item);
	}

	void Menu::Show()
	{
		int chosenItem = 0;
		int keyCode = 0;
		bool userHasChosenItem = false;
		Console::Key key;

		while (!userHasChosenItem)
		{
			Console::Clear();

			std::cout << title << std::endl;

			for (size_t i = 0; i < items.size(); ++i) {
				if (i == chosenItem) {
					std::cout << "# ";
				}

				std::cout << items[i].title << std::endl;
			}

			key = static_cast<Console::Key>(Console::GetChar());

			switch (key)
			{
			case Console::Key::Up:
				chosenItem = chosenItem == items.size() - 1 ? 0 : chosenItem + 1;
				break;
			case Console::Key::Down:
				chosenItem = chosenItem == items.size() - 1 ? 0 : chosenItem + 1;
				break;
			case Console::Key::Enter:
				userHasChosenItem = true;
				break;
			}
		}

		items[chosenItem].action();
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