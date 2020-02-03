#pragma once

#include "console.h"

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <conio.h>
#include <Windows.h>

struct MenuItem
{
	std::string title;
	std::function<void()> action;
};

class Menu
{
public:
	explicit Menu(std::string);
	void AddMenuItem(MenuItem);
	void Show();
private:
	std::string title;
	std::vector<MenuItem> items;
};
