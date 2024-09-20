#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <../glfw-3.4/include/GLFW/glfw3.h>

#include <string>
#include <iostream>

class Game
{
private:
    // CONSTANT MEMBER VARIABLES
    const unsigned int m_WIDTH;
    const unsigned int m_HEIGHT;
    const std::string m_TITLE;

    // Member Variables
    GLFWwindow* m_window;

public:
    Game(); // Default Constructor - Here to test if GLFW windowing works
    Game(unsigned int, unsigned int, std::string); // This constructor should be used for changing width, height and window title variables
    ~Game();
    void Run(); // Runs Game - Calls Init, ProgramLoop, and Shutdown
private:
    void Init();
    void ProgramLoop();
    void Render();
    void Update(float);
    void Shutdown();
    void ProcessInput();
};


void FrameBufferSize_Callback(GLFWwindow*, int, int);

#endif // GAME_H