#include "Game.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"



Game::Game() : m_WIDTH(1080), m_HEIGHT(720), m_TITLE("Hello Game!")
{
    m_window = nullptr;
}

Game::Game(unsigned int width, unsigned int height, std::string title) : m_WIDTH(width), m_HEIGHT(height), m_TITLE(title)
{
    m_window = nullptr;
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
    m_renderer = std::shared_ptr<Renderer>(new Renderer(ResourceManager::GetShader("sprite")));
    // Load Textures
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/block.png", "brick", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/block_solid.png", "solid_brick", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/background.jpg", "background", false);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/paddle.png", "paddle", true);
    ResourceManager::LoadTexture(RESOURCES_PATH "sprites/awesomeface.png", "ball", true);

    m_gameObjects = CreateGameObjects(); 
    m_levels = LoadLevels();

    // Current Level
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

    ResourceManager::FreeResources();    
    glfwTerminate();
}

void Game::ProcessInput(float deltaTime)
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    
    float playerVelo = m_PLAYERVELOCITY * deltaTime;
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (m_gameObjects[ID::PLAYER].m_pos.x >= 0.0f)
        {
            m_gameObjects[ID::PLAYER].m_pos.x -= playerVelo;
            if (m_gameObjects[ID::BALL].m_stuck)
            {
                m_gameObjects[ID::BALL].m_pos.x -= playerVelo;
            }
        }
    }

    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (m_gameObjects[ID::PLAYER].m_pos.x <= m_WIDTH - m_gameObjects[ID::PLAYER].m_size.x)
        {
            m_gameObjects[ID::PLAYER].m_pos.x += playerVelo;
            if (m_gameObjects[ID::BALL].m_stuck)
            {
                m_gameObjects[ID::BALL].m_pos.x += playerVelo;
            }
        }
    }
    
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        m_gameObjects[ID::BALL].m_stuck = false;
    }
}

void Game::ResetLevel()
{
    if (m_level == 0)
    {
        m_levels[0].Load(RESOURCES_PATH "levels/level1.txt", m_WIDTH, m_HEIGHT / 2);
    }
}

void Game::ResetPlayer()
{
    m_gameObjects[0].m_size = m_PLAYERSIZE;
    m_gameObjects[0].m_pos = glm::vec2(m_WIDTH / 2.0f - m_PLAYERSIZE.x / 2.0f, m_HEIGHT - m_PLAYERSIZE.y);
    m_gameObjects[1].Reset(m_gameObjects[0].m_pos + glm::vec2(m_PLAYERSIZE.x / 2.0f - m_BALLRADIUS, -m_BALLRADIUS * 2.0f), m_BALLVELOCITY);
}

std::vector<GameObject> Game::CreateGameObjects()
{
    std::shared_ptr<SpriteComponent> playerSprite(new SpriteComponent(ResourceManager::GetTexture("paddle")));
    GameObject playerObject = GameObject(m_PLAYERPOS, m_PLAYERSIZE, ID::PLAYER);
    playerObject.AddComponent(playerSprite);

    std::shared_ptr<SpriteComponent> ballSprite(new SpriteComponent(ResourceManager::GetTexture("ball")));
    glm::vec2 ballPos = m_PLAYERPOS + glm::vec2(m_PLAYERSIZE.x / 2.0f - m_BALLRADIUS, -m_BALLRADIUS * 2.0f);
    GameObject ballObject = GameObject(ballPos, glm::vec2(m_BALLRADIUS * 2.0f, m_BALLRADIUS * 2.0f), ID::BALL);
    ballObject.m_radius = m_BALLRADIUS;
    ballObject.m_velocity = m_BALLVELOCITY;
    ballObject.m_stuck = true;
    ballObject.AddComponent(ballSprite);

    std::vector<GameObject> returnGameObjects{ playerObject, ballObject };
    
    return returnGameObjects;
}

std::vector<Level> Game::LoadLevels()
{
    Level levelOne, levelTwo, levelThree, levelFour;
    levelOne.Load(RESOURCES_PATH "levels/level1.txt", m_WIDTH, m_HEIGHT / 2);
    levelTwo.Load(RESOURCES_PATH "levels/level2.txt", m_WIDTH, m_HEIGHT / 2);
    levelThree.Load(RESOURCES_PATH "levels/level3.txt", m_WIDTH, m_HEIGHT / 2);
    levelFour.Load(RESOURCES_PATH "levels/level4.txt", m_WIDTH, m_HEIGHT / 2);

    std::vector<Level> returnLoadedLevels{levelOne, levelTwo, levelThree, levelFour};
    return returnLoadedLevels;
}

Collision Game::CheckCollision(GameObject& one, GameObject& two)
{
    glm::vec2 center(one.m_pos + one.m_radius);
    glm::vec2 aabb_half_extents(two.m_size.x / 2.0f, two.m_size.y / 2.0f);
    glm::vec2 aabb_center(
        two.m_pos.x + aabb_half_extents.x,
        two.m_pos.y + aabb_half_extents.y
    );

    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;

    if (glm::length(difference) <= one.m_radius)
    {
        return std::make_tuple(true, VectorDirection(difference), difference);
    }
    else
    {
        return std::make_tuple(false, Direction::UP, glm::vec2(0.0f, 0.0f));
    }
}

void Game::DoCollisions()
{
    for (GameObject &box : m_levels[m_level].bricks)
    {
        if (!box.m_destroyed && !m_gameObjects[1].m_stuck)
        {
            Collision collision = CheckCollision(m_gameObjects[ID::BALL], box);
            if (std::get<0>(collision))
            {
                if (!box.m_isSolid)
                {
                    box.m_destroyed = true;
                }

                Direction dir = std::get<1>(collision);
                glm::vec2 diffVector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT)
                {
                    m_gameObjects[1].m_velocity.x = -m_gameObjects[1].m_velocity.x;
                    float penetration = m_gameObjects[1].m_radius - std::abs(diffVector.x);
                    if (dir == LEFT)
                    {
                        m_gameObjects[1].m_pos.x += penetration;
                    }
                    else
                    {
                        m_gameObjects[1].m_pos.x -= penetration;
                    }
                }
                else
                {
                    m_gameObjects[1].m_velocity.y = -m_gameObjects[1].m_velocity.y;
                    float penetration = m_gameObjects[1].m_radius - std::abs(diffVector.y);
                    if (dir == UP)
                    {
                        m_gameObjects[1].m_pos.y -= penetration;
                    }
                    else
                    {
                        m_gameObjects[1].m_pos.y += penetration;
                    }
                }
            }
        }
    }

    Collision result = CheckCollision(m_gameObjects[ID::BALL], m_gameObjects[0]);
    if (!m_gameObjects[ID::BALL].m_stuck && std::get<0>(result))
    {

        float centerBoard = m_gameObjects[0].m_pos.x + m_gameObjects[0].m_size.x / 2.0f;
        float distance = (m_gameObjects[ID::BALL].m_pos.x + m_gameObjects[ID::BALL].m_radius) - centerBoard;
        float percentage = distance / (m_gameObjects[0].m_size.x / 2.0f);

        float strength = 2.0f;
        glm::vec2 oldVelocity = m_gameObjects[1].m_velocity;
        m_gameObjects[ID::BALL].m_velocity.x = m_BALLVELOCITY.x * percentage * strength;;
        m_gameObjects[ID::BALL].m_velocity.y = -1.0f * std::abs(m_gameObjects[ID::BALL].m_velocity.y);
        m_gameObjects[ID::BALL].m_velocity = glm::normalize(m_gameObjects[ID::BALL].m_velocity) * glm::length(oldVelocity);
    }
}

Direction Game::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f), // up
        glm::vec2(1.0f, 0.0f), // right
        glm::vec2(0.0f, -1.0f), // Down
        glm::vec2(-1.0f, 0.0f) // left
    };

    float max = 0.0f;
    unsigned int bestMatch = -1;
    for (size_t i = 0; i < 4; i++)
    {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            bestMatch = i;
        }
    }
    return (Direction)bestMatch;
}

void Game::Update(float deltaTime)
{
    ProcessInput(deltaTime);
    m_gameObjects[ID::BALL].Move(deltaTime, m_WIDTH);
    DoCollisions();
    Render();
    if (m_gameObjects[ID::BALL].m_pos.y >= m_HEIGHT)
    {
        ResetLevel();
        ResetPlayer();
    }
}

void Game::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_renderer.get()->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(m_WIDTH, m_HEIGHT));

    m_levels[m_level].Draw(*m_renderer);
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        GameObject currentObject = m_gameObjects[i];
        currentObject.m_component[ComponentType::Sprite].get()->Draw(
            *m_renderer, 
            currentObject.m_pos, 
            currentObject.m_size,
            currentObject.m_rotation,
            currentObject.m_color);
    }
}

void FrameBufferSize_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}