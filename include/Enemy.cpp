#include "Enemy.h"
#include "GameplayScene.h"

#include <glm/glm.hpp>
#include <random>

Enemy::Enemy(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Enemy;

	mShader = &(mGame->GetShaderLibrary()->objectShader);
	mModel = &(mGame->GetModelLibrary()->carModel);

	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(0, mGame->GetModelLibrary()->enemyCarTextures.size()); // Define the range
	mTexture = &(mGame->GetModelLibrary()->enemyCarTextures[dis(gen)]);

	mHoverValue = dis(gen);
}

void Enemy::Update(float _deltaTime)
{
	mHoverValue += mHoverSpeed * _deltaTime;
	float hoverHeight = sin(mHoverValue);
	transform.position.y = hoverHeight * 0.25f;

	GameplayScene* gameplayScene = (GameplayScene*)mGame->GetCurrentScene();
	transform.position.z -= gameplayScene->GetGameSpeed() * _deltaTime;

	if (!mSpawnedNew && transform.position.z < mGame->GetCurrentScene()->GetPlayer()->transform.position.z)
	{
		std::random_device rd;  // Seed for the random number engine
		std::mt19937 gen(rd()); // Mersenne Twister engine
		std::uniform_real_distribution<> dis(-7.5f, 7.5f); // Define the range

		Enemy* enemy = new Enemy(mGame);
		enemy->transform.position = glm::vec3(dis(gen), 0.f, mGame->GetCurrentScene()->GetPlayer()->transform.position.z + 120.f);
		gameplayScene->AddGameObject(enemy);
		mSpawnedNew = true;
	}

	if (transform.position.z < -50.f)
	{
		gameplayScene->RemoveGameObject(this);
	}
}