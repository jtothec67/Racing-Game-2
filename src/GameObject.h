#pragma once

#include <glm/glm.hpp>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Game;

struct Transform
{
	glm::vec3 position = glm::vec3 (0.f, 0.f, 0.f);
	glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
};

class GameObject
{
public:
	GameObject(Game* _game);
	
	virtual ~GameObject();

	virtual void Update(float _deltaTime) {}
	virtual void Draw() {}

	Transform transform;

protected:
	Game* mGame;
};

#endif // GAMEOBJECT_H