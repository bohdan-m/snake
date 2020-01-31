#include <iostream>

#include "ui.h"

using namespace ui;

int main()
{
    Menu::MenuItem item1 = { "First", [] { std::cout << 1 << std::endl; } };
    Menu::MenuItem item2 = { "Second", [] { std::cout << 2 << std::endl; } };

    Menu menu("Menu");
    menu.AddMenuItem(item1);
    menu.AddMenuItem(item2);
    menu.Show();

    return 0;
}

