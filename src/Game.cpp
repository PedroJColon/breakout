#include "Game.h"
#include "ResourceManager.h"
#include "Renderer.h"

Renderer* renderer;

Game::Game() : m_WIDTH(1080), m_HEIGHT(720), m_TITLE("Hello Game!")
{
    m_window = 0;
    renderer = 0;
}

Game::Game(unsigned int width, unsigned int height, std::string title) : m_WIDTH(width), m_HEIGHT(height), m_TITLE(title)
{
    m_window = 0;
    renderer = 0;
}

Game::~Game()
{
}

void Game::Run()
{
    InitWindow();
    InitGame();
    ProgramLoop();
    Shutdown();
}

void Game::InitWindow()
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

void Game::InitGame()
{
    // Load Shaders
    std::string empty = {};
    ResourceManager::LoadShaders(RESOURCES_PATH "shaders/vertex.glsl", RESOURCES_PATH "shaders/fragment.glsl", empty, "face");
    // Set Camera
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_WIDTH), static_cast<float>(m_HEIGHT), 0.0f, -1.0f, 1.0f);
    // Configure our shaders
    ResourceManager::GetShader("face").ActivateShader();
    ResourceManager::GetShader("face").SetInt("image", 0);
    ResourceManager::GetShader("face").SetMatrix4f("projection", projection);
    // Set our renderer
    renderer = new Renderer(ResourceManager::GetShader("face"));
    // Load Textures
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/PogChamp_komodo.png", "face", true);
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
    if (renderer)
    {
        delete renderer;
        renderer = 0;
    }
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f,
        glm::vec3(0.0f, 1.0f, 0.0f));
}

void FrameBufferSize_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}