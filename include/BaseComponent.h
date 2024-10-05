#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include "Renderer.h"


enum ComponentType
{
	Sprite = 0,
};


class IBaseComponent
{
public:
	IBaseComponent() {};

	virtual void Draw(Renderer& renderer, glm::vec2, glm::vec2, float, glm::vec3) = 0;

private:

};

#endif // !BASECOMPONENT_H