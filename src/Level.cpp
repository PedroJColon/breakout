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
	for (auto &iter : bricks)
	{
		if (!iter.first.m_destroyed)
		{
			iter.second.Draw(renderer, iter.first.m_pos, iter.first.m_size, iter.first.m_rotation, iter.first.m_color);
		}
	}
}

bool Level::LevelCompleted()
{
	for (auto &tile : bricks)
	{
		if (!tile.first.m_isSolid && !tile.first.m_destroyed)
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
	float unitWidth = levelWidth / width;
	float unitHeight = levelHeight / height;

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			if (tileData[y][x] == 1)
			{
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);

				GameObject solidBrick(pos, size, glm::vec3(0.8f, 0.8f, 0.7f));
				Sprite solidBrickSprite(ResourceManager::GetTexture("solid_brick"));
				solidBrick.m_isSolid = true;
				bricks.push_back(std::make_pair(solidBrick, solidBrickSprite));
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
				GameObject brick(pos, size, color);
				Sprite brickSprite(ResourceManager::GetTexture("brick"));
				bricks.push_back(std::make_pair(brick, brickSprite));
			}
		}
	}
}
