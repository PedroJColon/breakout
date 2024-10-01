#ifndef LEVELS_H
#define LEVELS_H

#include <vector>
#include <string>
#include <iostream>
// find out file i/o stuff

#include "GameObject.h"
#include <Sprite.h>
#include "ResourceManager.h"
#include "Renderer.h"

class Level
{
public:
	// Hold Brich Object and Sprites
	std::vector<std::pair<GameObject, Sprite>> bricks;

	Level();
	~Level();

	// Load level from file
	void Load(std::string, unsigned int, unsigned int);
	// Render
	void Draw(Renderer&);
	// Check if our level is completed
	bool LevelCompleted();

private:
	void InitLevel(std::vector<std::vector<unsigned int>>, unsigned int levelWidth, unsigned int);
};


#endif // !LEVELS_H