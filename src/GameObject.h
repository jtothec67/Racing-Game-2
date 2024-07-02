#pragma once

#include "Model.h"
#include "Texture.h"
#include "Shader.h"

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

	virtual void SetModel(Model* _model) { mModel = _model; }
	virtual Model* GetModel() { return mModel; }

	virtual void SetTexture(Texture* _texture) { mTexture = _texture; }
	virtual Texture* GetTexture() { return mTexture; }

	virtual void SetShader(Shader* _shader) { mShader = _shader; }
	virtual Shader* GetShader() { return mShader; }

	Transform transform;

protected:
	Game* mGame;

	Model* mModel;
	Texture* mTexture;
	Shader* mShader;
};

#endif // GAMEOBJECT_H