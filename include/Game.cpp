#include "Game.h"
#include "Player.h"

Game::Game()
{
	mModelLibrary = new ModelLibrary();

	mWindow = new Window(1920, 1080);

	mCamera = new GameObject(this);

	Player myPlayer(this);
	AddGameObject(new Player(this));
}

Game::~Game()
{
	delete mWindow;
	delete mCamera;
	delete mModelLibrary;
	mGameObjects.clear();
	mGameObjectsToRemove.clear();
}

void Game::Run(float _deltaTime)
{
	Update(_deltaTime);
	Draw();

	mRemoveGameObjects();
}

void Game::Update(float _deltaTime)
{
	mWindow->Update();

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}
}

void Game::Draw()
{
	mWindow->ClearWindow();

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}

	mWindow->SwapWindows();
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