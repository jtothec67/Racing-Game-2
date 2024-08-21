#include "GameplayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Skybox.h"
#include "text.h"

#include <random>
#include <iostream>

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	Player* player = new Player(mGame);
	AddGameObject(player);
	mNamedGameObjects["Player"] = player;

	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	Text* scoreText = new Text(mGame);
	scoreText->transform.position = glm::vec3(100.f, windowHeight - 200.f, 0.f);
	scoreText->SetAnchor(Anchor::TopLeft);
	AddGameObject(scoreText);
	mNamedGameObjects["ScoreText"] = scoreText;


	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(-7.5f, 7.5f); // Define the range

	for (int i = 0; i < 4; i++)
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
	if (mCrashTimer.IsRunning() && mCrashTimer.GetElapsedTime() > mGameOverWaitTime)
	{
		mGame->ChangeScene(Scene::Menu);
	}

	if (mGameOver)
	{
		mGameSpeed -= mGameOverDecelSpeed * _deltaTime;
		
		if (mGameSpeed < 0.f)
			mGameSpeed = 0.f;
	}
	else
	{
		mGameSpeed += mGameSpeedAccel * _deltaTime;

		Text* scoreText = (Text*)mNamedGameObjects["ScoreText"];
		scoreText->SetText(std::to_string((int)mGameSpeed));
	}

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

void GameplayScene::Collision()
{
	if (mGameOver)
		return;

	mGameOver = true;
	mCrashTimer.Start();
	mGameOverDecelSpeed = mGameSpeed / mGameOverWaitTime;
}