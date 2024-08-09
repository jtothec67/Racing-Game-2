#include "GameplayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Skybox.h"

#include <random>
#include <iostream>

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	Player* player = new Player(mGame);

	AddGameObject(player);
	mNamedGameObjects["Player"] = player;

	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(-7.5f, 7.5f); // Define the range

	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Enemy(mGame);
		enemy->transform.position = glm::vec3(dis(gen), 0.f, 40.f + (40.f * i));
		AddGameObject(enemy);
	}
}

GameplayScene::~GameplayScene()
{
	
}

void GameplayScene::Update(float _deltaTime)
{
	if (mGame->keyDown[SDLK_p])
	{
		mGame->ChangeScene(Scene::Menu);
		return;
	}

	mGameSpeed += mGameSpeedAccel * _deltaTime;

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}
	
	mLightPos = glm::vec3(0.f, 20.f, mNamedGameObjects["Player"]->transform.position.z - 10.f);

	glm::vec3 camPos = mNamedGameObjects["Player"]->transform.position + glm::vec3(0.f, 0.f, -10.f);
	camPos.y = 7.f;
	mGame->GetCamera()->transform.position = camPos;

	mGame->GetCamera()->transform.rotation.x = -25.f;

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