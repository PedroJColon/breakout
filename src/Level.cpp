#include "Level.h"


Level::Level()
{
}

Level::~Level()
{
}

void Level::Load(std::string file, unsigned int levelWidth, unsigned int levelHeight)
{
	bricks.clear();

	unsigned int tileCode;
	Level level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
		{
			InitLevel(tileData, levelWidth, levelHeight);
		}
	}
}

void Level::Draw(Renderer& renderer)
{
	for (auto &brick : bricks)
	{
		if (!brick.m_destroyed)
		{
			brick.m_component[ComponentType::Sprite].get()->Draw(renderer, brick.m_pos, brick.m_size, brick.m_rotation, brick.m_color);
		}
	}
}

bool Level::LevelCompleted()
{
	for (auto &tile : bricks)
	{
		if (!tile.m_isSolid && !tile.m_destroyed)
		{
			return false;
		}
	}
	return true;
}

void Level::InitLevel(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{

	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unitWidth = levelWidth / static_cast<float>(width);
	float unitHeight = levelHeight / height;

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (tileData[y][x] == 1)
			{
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);

				GameObject solidBrick(pos, size, ID::SOLIDBRICK, glm::vec3(0.8f, 0.8f, 0.7f));
				std::shared_ptr<SpriteComponent> solidBrickSprite(new SpriteComponent(ResourceManager::GetTexture("solid_brick")));
				solidBrick.AddComponent(solidBrickSprite);
				solidBrick.m_isSolid = true;
				bricks.push_back(solidBrick);
			}
			else if (tileData[y][x] > 1)
			{
				glm::vec3 color = glm::vec3(1.0f); 

				if (tileData[y][x] == 2)
				{
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				}
				else if (tileData[y][x] == 3)
				{
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				}
				else if (tileData[y][x] == 4)
				{
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				}
				else if (tileData[y][x] == 5)
				{
					color = glm::vec3(1.0f, 0.5f, 0.0f);
				}

				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject brick(pos, size, ID::BRICK, color);
				std::shared_ptr<SpriteComponent> brickSprite(new SpriteComponent(ResourceManager::GetTexture("brick")));
				brick.AddComponent(brickSprite);
				bricks.push_back(brick);
			}
		}
	}
}
