#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Game
{
private:
    /* data */
public:
    Game(/* args */);
    ~Game();
    void Init();
    void Update(float);
    void Render();
private:

};



#endif // GAME_H