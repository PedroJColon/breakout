// INCLUDES
#include <iostream>
#include <string>

// MY CLASS INCLUDES
#include "Game.h"

int main()
{
    std::string title = "BREAKOUT";
    int width = 1920;
    int height = 1080;

    Game game(width, height, title);
    try
    {
        game.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error Reason: " << e.what() << '\n' << std::endl;
    }
    
    return 0;
}