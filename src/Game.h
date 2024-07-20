#pragma once

#include "BaseScene.h"
#include "Window.h"
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

	BaseScene* GetCurrentScene();

	GameObject* GetCamera() { return &mCamera; }

	Window* GetWindow() { return &mWindow; }
	void GetWindowSize(int& _width, int& _height) { mWindow.GetWindowSize(_width, _height); }

	void StopGameRunning() { gameRunning = false; }
	bool IsGameRunning() { return gameRunning; }

	ModelLibrary* GetModelLibrary() { return &mModelLibrary; }
	ShaderLibrary* GetShaderLibrary() { return &mShaderLibrary; }

	std::map<int, bool> keyboard;

private:
	void Update(float _deltaTime);
	void Draw();

	void SetGlobalUniforms();

	void CheckUserInput();

	std::vector<BaseScene*> mScenes;

	SDL_Event event = {};

	Window mWindow;

	Camera mCamera;

	ModelLibrary mModelLibrary;
	ShaderLibrary mShaderLibrary;

	bool gameRunning = true;
};