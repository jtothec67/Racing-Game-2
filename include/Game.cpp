#include "Game.h"
#include "Player.h"
#include "UIObject.h"
#include "Skybox.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

Game::Game()
	: mWindow(1920, 1080)
	, mCamera(this, 45, 0.1f, 100.f)
{
	AddGameObject(new Player(this));
	AddGameObject(new UIObject(this));
	AddGameObject(new Skybox(this));
}

Game::~Game()
{
	mGameObjects.clear();
	mGameObjectsToRemove.clear();
}

void Game::Run(float _deltaTime)
{
	Update(_deltaTime); // deltaTime is the time the last frame took to update and draw (in seconds)
	Draw();
}

void Game::Update(float _deltaTime)
{
	mWindow.Update();

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}

	mRemoveGameObjects();
}

void Game::Draw()
{
	mWindow.ClearWindow();

	SetGlobalUniforms();

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}

	mWindow.SwapWindows();
}

void Game::mRemoveGameObjects()
{
    if (mGameObjectsToRemove.empty())
        return;

    for (auto* objToRemove : mGameObjectsToRemove)
    {
        for (auto it = mGameObjects.rbegin(); it != mGameObjects.rend(); ++it)
        {
            if (*it == objToRemove)
            {
                mGameObjects.erase((it + 1).base());
                break; 
            }
        }
    }

    mGameObjectsToRemove.clear();
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
	mShaderLibrary.objectShader.uniform("u_LightPos", mLightPos);


	glm::mat4 uiProjection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.0f);

	mShaderLibrary.uiShader.uniform("u_Projection", uiProjection);
	mShaderLibrary.uiShader.uniform("u_View", glm::mat4(1.0f));


	glm::mat4 invPV = glm::inverse(projection * view);

	mShaderLibrary.skyboxShader.uniform("invPV", invPV);
}