#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <conio.h>

namespace ui {
	class Menu 
	{
	public:
		struct MenuItem
		{
			std::string title;
			std::function<void()> action;
		};

		explicit Menu(std::string);
		void AddMenuItem(MenuItem item);
		void Show();
	private:
		std::string title;
		std::vector<MenuItem> items;
	};


	class Console
	{
	public:
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
	};

};
