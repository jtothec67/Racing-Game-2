#include "Game.h"
#include "MenuScene.h"
#include "GameplayScene.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

Game::Game()
	: mWindow(1920, 1080)
	, mCamera(this, 45, 0.1f, 100.f)
{
	mCurrentScene = new MenuScene(this);
}

Game::~Game()
{
	delete mCurrentScene;
}

void Game::Run(float _deltaTime)
{
	Update(_deltaTime); // deltaTime is the time the last frame took to update and draw (in seconds)
	Draw();
}

void Game::Update(float _deltaTime)
{
	mWindow.Update();

	CheckUserInput();

	mCurrentScene->Update(_deltaTime);
}

void Game::Draw()
{
	mWindow.ClearWindow();

	SetGlobalUniforms();

	mCurrentScene->Draw();

	mWindow.SwapWindows();
}

void Game::ChangeScene(Scene _scene)
{
	delete mCurrentScene;
	switch (_scene)
	{
	case Scene::Menu:
		mCurrentScene = new MenuScene(this);
		break;
	case Scene::Game:
		mCurrentScene = new GameplayScene(this);
		break;
	}
}

void Game::SetGlobalUniforms()
{
	int width, height;
	GetWindowSize(width, height);
	glm::mat4 projection = glm::perspective(glm::radians(mCamera.GetFOV()), (float)width / (float)height, mCamera.GetNearClip(), mCamera.GetFarClip());

	glm::mat4 view(1.0f);
	view = glm::translate(view, mCamera.transform.position);
	view = glm::rotate(view, glm::radians(mCamera.transform.rotation.x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(mCamera.transform.rotation.y), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(mCamera.transform.rotation.z), glm::vec3(0, 0, 1));
	view = glm::inverse(view);

	mShaderLibrary.objectShader.uniform("u_Projection", projection);
	mShaderLibrary.objectShader.uniform("u_View", view);
	mShaderLibrary.objectShader.uniform("u_LightPos", GetCurrentScene()->GetLightPos());


	glm::mat4 uiProjection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.0f);

	mShaderLibrary.uiShader.uniform("u_Projection", uiProjection);
	mShaderLibrary.uiShader.uniform("u_View", glm::mat4(1.0f));


	glm::mat4 invPV = glm::inverse(projection * view);

	mShaderLibrary.skyboxShader.uniform("invPV", invPV);
}

void Game::CheckUserInput()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			StopGameRunning();
		}

		if (event.type == SDL_KEYDOWN)
		{
			keyboard[event.key.keysym.sym] = true;
		}

		if (event.type == SDL_KEYUP)
		{
			keyboard[event.key.keysym.sym] = false;
		}
	}
}