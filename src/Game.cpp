#include "Game.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Sprite.h"

Renderer* renderer;
Sprite* playerSprite;

const float velocity = 500.0f;

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
    ResourceManager::LoadShaders(RESOURCES_PATH "shaders/vertex.glsl", RESOURCES_PATH "shaders/fragment.glsl", empty, "sprite");
    // Set Camera
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_WIDTH), static_cast<float>(m_HEIGHT), 0.0f, -1.0f, 1.0f);
    // Configure our shaders
    ResourceManager::GetShader("sprite").ActivateShader();
    ResourceManager::GetShader("sprite").SetInt("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4f("projection", projection);
    // Set our renderer
    renderer = new Renderer(ResourceManager::GetShader("sprite"));
    // Load Textures
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/block.png", "brick", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/block_solid.png", "solid_brick", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/background.jpg", "background", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/paddle.png", "paddle", true);
    

    glm::vec2 playerSize(100.0f, 20.0f);
    glm::vec2 playerPos = glm::vec2(
    m_WIDTH / 2.0f - playerSize.x /2, m_HEIGHT - playerSize.y);

    playerSprite = new Sprite(ResourceManager::GetTexture("paddle"));
    m_player = GameObject(playerPos, playerSize);

    Level levelOne, levelTwo, levelThree, levelFour;
    levelOne.Load(RESOURCES_PATH "levels/level1.txt", m_WIDTH, m_HEIGHT / 2);
    levelTwo.Load(RESOURCES_PATH "levels/level2.txt", m_WIDTH, m_HEIGHT / 2);
    levelThree.Load(RESOURCES_PATH "levels/level3.txt", m_WIDTH, m_HEIGHT / 2);
    levelFour.Load(RESOURCES_PATH "levels/level4.txt", m_WIDTH, m_HEIGHT / 2);

    m_levels.push_back(levelOne);
    m_levels.push_back(levelTwo);
    m_levels.push_back(levelThree);
    m_levels.push_back(levelFour);
    m_level = 0;


}

void Game::ProgramLoop()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(m_window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        Update(deltaTime);
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
    if (playerSprite)
    {
        delete playerSprite;
        playerSprite = 0;
    }
    
    glfwTerminate();
}

void Game::ProcessInput(float deltaTime)
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    
    float playerVelo = velocity * deltaTime;
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (m_player.m_pos.x >= 0.0f)
        {
            m_player.m_pos.x -= playerVelo;
        }
    }

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (m_player.m_pos.x <= m_WIDTH - m_player.m_size.x)
        {
            m_player.m_pos.x += playerVelo;
        }
    }
}

void Game::Update(float deltaTime)
{
    ProcessInput(deltaTime);
    Render();
}

void Game::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(m_WIDTH, m_HEIGHT));

    m_levels[m_level].Draw(*renderer);
    playerSprite->Draw(*renderer, m_player.m_pos, m_player.m_size, m_player.m_rotation, m_player.m_color);
}

void FrameBufferSize_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}