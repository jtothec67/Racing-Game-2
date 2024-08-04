#pragma once

#include <glm/glm.hpp>

class Game;

struct Transform
{
	glm::vec3 position = glm::vec3 (0.f, 0.f, 0.f);
	glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);

	glm::vec3 GetForward()
	{
		glm::vec3 forward;
		forward.x = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
		forward.y = sin(glm::radians(rotation.x));
		forward.z = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));

		return glm::normalize(forward);
	}
};

enum class Tag
{
	NoTag,
	UI,
	Button,
	Player,
	Enemy,
	Environment,
	Skybox
};

class GameObject
{
public:
	GameObject(Game* _game);
	
	virtual ~GameObject();

	virtual void Update(float _deltaTime) {}
	virtual void Draw() {}

	Tag GetTag() { return mTag; }

	Transform transform;

protected:
	Game* mGame;

	Tag mTag = Tag::NoTag;
};