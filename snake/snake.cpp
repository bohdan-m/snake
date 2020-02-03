#include <iostream>

#include "menu.h"
#include "game.h"

int main()
{
    Game game;
    MenuItem item1 = { "New game", [&game] { game.Start(); } };
    MenuItem item2 = { "About", [] { } };

    Menu menu("Menu");
    menu.AddMenuItem(item1);
    menu.AddMenuItem(item2);
    menu.Show();

    return 0;
}

