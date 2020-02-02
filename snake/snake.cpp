#include <iostream>

#include "ui.h"
#include "game.h"

using namespace ui;

int main()
{
    Game game;
    Menu::MenuItem item1 = { "New game", [&game] { game.Start(); } };
    Menu::MenuItem item2 = { "About", [] { } };

    Menu menu("Menu");
    menu.AddMenuItem(item1);
    menu.AddMenuItem(item2);
    menu.Show();

    return 0;
}

