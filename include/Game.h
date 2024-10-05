#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <../glfw-3.4/include/GLFW/glfw3.h>
#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>

#include "Level.h"
#include "Renderer.h"

#include <string>
#include <iostream>

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;


class Game
{
private:
    // CONSTANT MEMBER VARIABLES
    const unsigned int m_WIDTH;
    const unsigned int m_HEIGHT;
    const std::string m_TITLE;

    // Member Variables
    GLFWwindow* m_window;
    std::shared_ptr<Renderer> m_renderer;
    std::vector<GameObject> m_gameObjects;

    const float m_PLAYERVELOCITY = 500.0f;
    const float m_BALLRADIUS = 12.5f;
    const glm::vec2 m_PLAYERSIZE = { 100.0f, 20.0f };
    const glm::vec2 m_BALLVELOCITY = { 100.0f, -350.0f };


    std::vector<Level> m_levels;
    unsigned int m_level;

public:
    Game(); // Default Constructor - Here to test if GLFW windowing works
    Game(unsigned int, unsigned int, std::string); // This constructor should be used for changing width, height and window title variables
    ~Game();
    void Run(); // Runs Game - Calls Init, ProgramLoop, and Shutdown
private:
    void InitWindow();
    void InitGame();
    void ProgramLoop();
    void Render();
    void Update(float);
    void Shutdown();
    void ProcessInput(float);
    void ResetLevel();
    void ResetPlayer();

    Collision CheckCollision(GameObject&, GameObject&);
    void DoCollisions();
    Direction VectorDirection(glm::vec2);
};


void FrameBufferSize_Callback(GLFWwindow*, int, int);

#endif // GAME_H