#include "GameplayScene.h"
#include "Player.h"
#include "Skybox.h"

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	AddGameObject(new Player(mGame));
}

GameplayScene::~GameplayScene()
{
	
}

void GameplayScene::Update(float _deltaTime)
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}

	mRemoveGameObjects();
}

void GameplayScene::Draw()
{
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}
}