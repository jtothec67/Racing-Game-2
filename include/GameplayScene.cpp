#include "GameplayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Track.h"
#include "Skybox.h"
#include "text.h"

#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	mDisplayFPS.Start();

	mGame->GetWindow()->SetClearColour(glm::vec4(1.0f, 0.f, 0.f, 0.f));

	InitialiseSceneObjects();
}

GameplayScene::~GameplayScene()
{
	
}

void GameplayScene::Update(float _deltaTime)
{
	// Display FPS
	if (mDisplayFPS.GetElapsedSeconds() > 0.5f)
	{
		Text* fpsText = (Text*)mNamedGameObjects["FPSText"];
		fpsText->SetText(std::to_string((int)(1.f / _deltaTime)));

		mDisplayFPS.Start();
	}

	if (mCrashTimer.IsRunning() && mCrashTimer.GetElapsedSeconds() > mGameEndingWaitTime)
	{
		mGame->ChangeScene(Scene::Menu);
	}

	if (mGameEnding)
	{
		mGameSpeed -= mGameEndingDecelSpeed * _deltaTime;
		
		if (mGameSpeed < 0.f)
			mGameSpeed = 0.f;

		Text* multiplierText = (Text*)mNamedGameObjects["MultiplierText"];
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << mScoreMultiplier;
		multiplierText->SetText("x" + ss.str());

		Text* gameSpeedText = (Text*)mNamedGameObjects["GameSpeedText"];
		gameSpeedText->SetText(std::to_string((int)mGameSpeed));
	}
	else
	{
		mGameSpeed += mGameSpeedAccel * _deltaTime;

		mScore += mGameSpeedAccel * mScoreMultiplier * _deltaTime;

        Text* multiplierText = (Text*)mNamedGameObjects["MultiplierText"];
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << mScoreMultiplier;
        multiplierText->SetText("x" + ss.str());

		Text* scoreText = (Text*)mNamedGameObjects["ScoreText"];
		scoreText->SetText(std::to_string((int)mScore));

		Text* gameSpeedText = (Text*)mNamedGameObjects["GameSpeedText"];
		gameSpeedText->SetText(std::to_string((int)mGameSpeed));
	}

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}
	
	mLightPos = glm::vec3(0.f , 100.f, mNamedGameObjects["Player"]->transform.position.z - 20.f);

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

void GameplayScene::InitialiseSceneObjects()
{
	Player* player = new Player(mGame);
	AddGameObject(player);
	mNamedGameObjects["Player"] = player;

	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	Text* gameSpeedText = new Text(mGame);
	gameSpeedText->transform.position = glm::vec3(200.f, windowHeight - 200.f, 0.f);
	gameSpeedText->SetAnchor(Anchor::TopLeft);
	AddGameObject(gameSpeedText);
	mNamedGameObjects["GameSpeedText"] = gameSpeedText;

	Text* scoreText = new Text(mGame);
	scoreText->transform.position = glm::vec3(windowWidth - 200.f, windowHeight - 200.f, 0.f);
	scoreText->SetAnchor(Anchor::TopRight);
	AddGameObject(scoreText);
	mNamedGameObjects["ScoreText"] = scoreText;

	Text* multiplierText = new Text(mGame);
	multiplierText->transform.position = glm::vec3(windowWidth - 200.f, windowHeight / 2.f, 0.f);
	multiplierText->SetAnchor(Anchor::RightCenter);
	AddGameObject(multiplierText);
	mNamedGameObjects["MultiplierText"] = multiplierText;

	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(-7.5f, 7.5f); // Define the range

	for (int i = 0; i < 5; i++)
	{
		Enemy* enemy = new Enemy(mGame);
		enemy->transform.position = glm::vec3(dis(gen), 0.f, 50.f + (40.f * i));
		AddGameObject(enemy);
	}

	for (int i = 0; i < 3; i++)
	{
		Track* track = new Track(mGame);
		track->transform.position.z = (i * track->GetLength());
		AddGameObject(track);
	}

	threeDObject* grass = new threeDObject(mGame);
	grass->SetModel(mGame->GetModelLibrary()->grassModel);
	grass->SetTexture(mGame->GetModelLibrary()->trackAndGrassTexture);
	grass->transform.scale.z = 2.f;
	grass->transform.scale.x = 0.25f;
	grass->transform.position = glm::vec3(0.f, -2.25f, 0.f);
	grass->SetSpecular(false);
	AddGameObject(grass);

	Text* fpsText = new Text(mGame);
	fpsText->transform.position = glm::vec3(40.f, windowHeight - 20.f, 0.f);
	fpsText->SetColour(glm::vec3(0.f, 1.f, 0.f));
	fpsText->transform.scale.x = 0.2f;
	fpsText->SetAnchor(Anchor::TopLeft);
	AddGameObject(fpsText);
	mNamedGameObjects["FPSText"] = fpsText;
}

void GameplayScene::Collision()
{
	if (mGameEnding)
		return;

	mGameEnding = true;
	mCrashTimer.Start();
	mGameEndingDecelSpeed = mGameSpeed / mGameEndingWaitTime;
}