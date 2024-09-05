#include "Application.h"

Application::Application(int width, int height, std::string title) : m_WIDTH(width), m_HEIGHT(height), m_TITLE(title)
{
    m_game = 0;
}


Application::~Application()
{
}

void Application::Run()
{
    Init(m_WIDTH, m_HEIGHT, m_TITLE.c_str());
    MainLoop();
    Shutdown();
}

int Application::Init(int width, int height, std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(m_window, FrameBufferSize_Callback);
    return 0;
}

void Application::MainLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwSwapBuffers(m_window);
        ProcessInput(m_window);
        m_game->Render();
        m_game->Update(0);
        glfwPollEvents();
    }
    return;
}

void Application::Shutdown()
{
    glfwDestroyWindow(m_window);

    if (m_game)
    {
        delete m_game;
        m_game = 0;
    }
    
    glfwTerminate();
}

void Application::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    // Gameplay Keys
    // TODO: Pass inputs to Game Class to effect Player object state
}

void FrameBufferSize_Callback(GLFWwindow* window, int width, int height)
{ 
    glViewport(0,0, width, height);
}
