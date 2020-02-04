#include <iostream>

#include "menu.h"
#include "game.h"

int main()
{
    std::string about = "The Snake \nVersion 1.0 \nCopyright 2020 Bohdan Moiseienko \n\nPress any key to return to main menu.";
    Game game;
    Menu menu("The Snake");
    MenuItem item1 = { "New game", [&game] { game.Start(); } };
    MenuItem item2 = 
    { "About", [&about, &menu] 
        { 
            std::cout << about; 
            std::cin.get();
            menu.Show();
        } 
    };
    MenuItem item3 = { "Exit", [] {} };
    menu.AddMenuItem(item1);
    menu.AddMenuItem(item2);
    menu.AddMenuItem(item3);
    menu.Show();

    return 0;
}

