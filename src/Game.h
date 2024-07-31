#pragma once

#include "BaseScene.h"
#include "Window.h"
#include "ModelLibrary.h"
#include "ShaderLibrary.h"
#include "Camera.h"
#include "Timer.h"

#include <glm/glm.hpp>

#include <unordered_map>
#include <vector>

enum class Scene
{
	Menu,
	Game
};

class Game
{
public:
	Game();
	~Game();

	void Run();

	BaseScene* GetCurrentScene() { return mCurrentScene; }

	void ChangeScene(Scene _scene);

	Camera* GetCamera() { return &mCamera; }

	void UseCamera(Camera* _camera);

	Window* GetWindow() { return &mWindow; }
	void GetWindowSize(int& _width, int& _height) { mWindow.GetWindowSize(_width, _height); }

	void StopGameRunning() { mGameRunning = false; }
	bool IsGameRunning() { return mGameRunning; }

	ModelLibrary* GetModelLibrary() { return &mModelLibrary; }
	ShaderLibrary* GetShaderLibrary() { return &mShaderLibrary; }

	std::unordered_map<int, bool> keyPress;
	std::unordered_map<int, bool> keyDown;
	std::unordered_map<int, bool> keyUp;

private:
	void Update(float _deltaTime);
	void Draw();

	void CheckUserInput();

	Timer mFrameTimer;

	BaseScene* mCurrentScene;

	SDL_Event event = {};

	Window mWindow;

	Camera mCamera;

	ModelLibrary mModelLibrary;
	ShaderLibrary mShaderLibrary;

	bool mGameRunning = true;

	bool mSceneChanged = false;
};