#include "Game.h"

Game::Game() : m_WIDTH(1080), m_HEIGHT(720), m_TITLE("Hello Game!")
{
    m_window = 0;
}

Game::Game(unsigned int width, unsigned int height, std::string title) : m_WIDTH(width), m_HEIGHT(height), m_TITLE(title)
{
    m_window = 0;
}

Game::~Game()
{
}

void Game::Run()
{
    Init();
    ProgramLoop();
    Shutdown();
}

void Game::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(m_WIDTH, m_HEIGHT, m_TITLE.c_str(), NULL, NULL);
    if (!m_window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return;
    }

    glfwSetFramebufferSizeCallback(m_window, FrameBufferSize_Callback);
}

void Game::ProgramLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {

        glfwPollEvents();
        ProcessInput();
        Update(0);
        Render();
        glfwSwapBuffers(m_window);
    }
}

void Game::Shutdown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Game::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}

void Game::Update(float deltaTime)
{

}

void Game::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    
}

void FrameBufferSize_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}