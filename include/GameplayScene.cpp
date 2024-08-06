#include "GameplayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Skybox.h"
#include <iostream>

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	Player* player = new Player(mGame);

	AddGameObject(player);
	mNamedGameObjects["Player"] = player;


	Enemy* enemy = new Enemy(mGame);
	enemy->transform.position = glm::vec3(0.f, 0.f, 20.f);
	AddGameObject(enemy);
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
	
	mGame->GetCamera()->transform.rotation = mNamedGameObjects["Player"]->transform.rotation;

	glm::vec3 camPos = mNamedGameObjects["Player"]->transform.position + -(mNamedGameObjects["Player"]->transform.GetForward() * 10.f);
	camPos.y += 5.f;
	mGame->GetCamera()->transform.position = camPos;

	mGame->GetCamera()->transform.rotation.x = -20.f;

	mRemoveGameObjects();
}

void GameplayScene::Draw()
{
	mGame->UseCamera(mGame->GetCamera());

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}
}