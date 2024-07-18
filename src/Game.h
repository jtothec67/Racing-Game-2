#pragma once

#include "Window.h"
#include "GameObject.h"
#include "ModelLibrary.h"
#include "ShaderLibrary.h"
#include "Camera.h"

#include <glm/glm.hpp>

#include <map>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void Run(float _deltaTime);

	GameObject* GetCamera() { return &mCamera; }

	Window* GetWindow() { return &mWindow; }
	void GetWindowSize(int& _width, int& _height) { mWindow.GetWindowSize(_width, _height); }

	void AddGameObject(GameObject* _gameObject) { mGameObjects.push_back(_gameObject); }
	const std::vector<GameObject*>* GetGameObjects() { return &mGameObjects; }
	
	void RemoveGameObject(GameObject* _gameObject) { mGameObjectsToRemove.push_back(_gameObject); }

	void StopGameRunning() { gameRunning = false; }
	bool IsGameRunning() { return gameRunning; }

	ModelLibrary* GetModelLibrary() { return &mModelLibrary; }
	ShaderLibrary* GetShaderLibrary() { return &mShaderLibrary; }

	glm::vec3 GetLightPos() { return mLightPos; }

	std::map<int, bool> keyboard;

private:
	void Update(float _deltaTime);
	void Draw();

	void mRemoveGameObjects();

	void SetGlobalUniforms();

	void CheckUserInput();

	SDL_Event event = {};

	Window mWindow;

	Camera mCamera;

	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mGameObjectsToRemove;

	ModelLibrary mModelLibrary;
	ShaderLibrary mShaderLibrary;

	glm::vec3 mLightPos = glm::vec3(0.0f, 20.0f, 0.0f);

	bool gameRunning = true;
};