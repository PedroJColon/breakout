// INCLUDES
#include <iostream>
#include <string>

// MY CLASS INCLUDES
#include "Application.h"

int main()
{
    std::string title = "BREAKOUT";
    int width = 800;
    int height = 600;
    Application app(width, height, title.c_str());
    try
    {
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}