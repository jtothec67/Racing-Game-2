#include "Game.h"
#include "MenuScene.h"
#include "GameplayScene.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

Game::Game()
	: mWindow(1920, 1080)
	, mCamera(this, 45, 0.1f, 200.f)
{
	mCurrentScene = new MenuScene(this);

	// First deltaTime very small but that's fine
	mFrameTimer.Start();
}

Game::~Game()
{
	delete mCurrentScene;
}

void Game::Run()
{
	

	float deltaTime = mFrameTimer.Stop();

	mFrameTimer.Start();

	// Avoids first frame after scene has been changed being very long due to scene initialising
	if (mSceneChanged)
	{
		deltaTime = 0;
		mSceneChanged = false;
	}

	Update(deltaTime); // deltaTime is the time the last frame took to update and draw (in seconds)

	Draw();

	if (mSceneChanged)
	{
		// Swap scenes before draw because drawing takes a long time for a new scene (not sure why)
		// (EDIT: It's because the openGL objects are implimented using lazy loading, so the id only gets created the first time they are needed to be used. Will work on changing.)
		// (EDIT 2: Changed where I can, but not possible in the mesh class due to how adding faces after class is initialised, could do it every time a face is added but would cause a long initial load time.)
		// so next frame will be longer but we will set deltaTime to 0 for that frame.
		// Also being done after update so that we don't destroy the current scene when it's still in the middle of updating
		SwapScenes();
	}
	
	//std::cout << "FPS: " << 1.f /  deltaTime << std::endl; // Uses vsync if monitor has gsync/freesync
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

	mCurrentScene->Draw();

	mWindow.SwapWindows();
}

void Game::SwapScenes()
{
	delete mCurrentScene;

	switch (mNextScene)
	{
	case Scene::Menu:
	{
		mCurrentScene = new MenuScene(this);
		break;
	}
	case Scene::Game:
	{
		mCurrentScene = new GameplayScene(this);
		break;
	}
	}
}

void Game::UseCamera(Camera* _camera)
{
	int width, height;
	GetWindowSize(width, height);
	glm::mat4 projection = glm::perspective(glm::radians(_camera->GetFOV()), (float)width / (float)height, _camera->GetNearClip(), _camera->GetFarClip());

	glm::mat4 view(1.0f);
	view = glm::translate(view, _camera->transform.position);
	
	view = glm::rotate(view, glm::radians(_camera->transform.rotation.y + 180.f), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(_camera->transform.rotation.x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(_camera->transform.rotation.z), glm::vec3(0, 0, 1));
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
	keyDown.clear();
	keyUp.clear();

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			StopGameRunning();
		}

        if (event.type == SDL_KEYDOWN)
        {
            if (!keyPress[event.key.keysym.sym])
            {
                keyDown[event.key.keysym.sym] = true;
            }

            keyPress[event.key.keysym.sym] = true;
        }

		if (event.type == SDL_KEYUP)
		{
			keyUp[event.key.keysym.sym] = true;
			keyPress[event.key.keysym.sym] = false;
		}
	}
}