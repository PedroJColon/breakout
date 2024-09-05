#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"

#include <string>
#include <iostream>

class Application
{
private:
    // CONSTANT MEMBER VARIABLES
    const unsigned int m_WIDTH;
    const unsigned int m_HEIGHT;
    const std::string m_TITLE;

    // MEMBER VARIABLES
    GLFWwindow* m_window;
    Game* m_game;
    
public:
    Application(int, int, std::string);
    ~Application();
    void Run();

private:
    int Init(int, int, std::string);
    void MainLoop();
    void Shutdown();
    void ProcessInput(GLFWwindow*);

};

void FrameBufferSize_Callback(GLFWwindow*, int, int);

#endif // APPLICATION_H