#include "Enemy.h"
#include "GameplayScene.h"

#include <glm/glm.hpp>
#include <random>

Enemy::Enemy(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Enemy;

	mModel = &(mGame->GetModelLibrary()->carModel);

	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(0, mGame->GetModelLibrary()->enemyCarTextures.size()); // Define the range
	mTexture = &(mGame->GetModelLibrary()->enemyCarTextures[dis(gen)]);

	mHoverValue = dis(gen);

	// Figures come from testing model in Unity
	mBoundingBox.offset.y = 0.2f;
	mBoundingBox.offset.z = 0.54f;

	mBoundingBox.widthX = 3.2f;
	mBoundingBox.heightY = 1.7f;
	mBoundingBox.depthZ = 8.4f;
}

void Enemy::Update(float _deltaTime)
{
	mHoverValue += mHoverSpeed * _deltaTime;
	float hoverHeight = sin(mHoverValue);
	transform.position.y = hoverHeight * 0.25f;

	GameplayScene* gameplayScene = (GameplayScene*)mGame->GetCurrentScene();
	transform.position.z -= gameplayScene->GetGameSpeed() * _deltaTime;

	threeDObject* player = (threeDObject*)mGame->GetCurrentScene()->GetPlayer();
	
	if (player == nullptr)
		return;

	BoundingBox playerBB = player->GetBoundingBox();

	glm::vec3 enemyMin = transform.position + mBoundingBox.offset - glm::vec3(mBoundingBox.widthX / 2, mBoundingBox.heightY / 2, mBoundingBox.depthZ / 2);
	glm::vec3 enemyMax = transform.position + mBoundingBox.offset + glm::vec3(mBoundingBox.widthX / 2, mBoundingBox.heightY / 2, mBoundingBox.depthZ / 2);

	glm::vec3 playerMin = player->transform.position + playerBB.offset - glm::vec3(playerBB.widthX / 2, playerBB.heightY / 2, playerBB.depthZ / 2);
	glm::vec3 playerMax = player->transform.position + playerBB.offset + glm::vec3(playerBB.widthX / 2, playerBB.heightY / 2, playerBB.depthZ / 2);

	// Check for collision
	bool collisionX = enemyMin.x <= playerMax.x && enemyMax.x >= playerMin.x;
	bool collisionY = enemyMin.y <= playerMax.y && enemyMax.y >= playerMin.y;
	bool collisionZ = enemyMin.z <= playerMax.z && enemyMax.z >= playerMin.z;

	if (collisionX && collisionY && collisionZ)
	{
		gameplayScene->Collision();
		return;
	}

	if (!mSpawnedNew && transform.position.z < player->transform.position.z)
	{
		std::random_device rd;  // Seed for the random number engine
		std::mt19937 gen(rd()); // Mersenne Twister engine
		std::uniform_real_distribution<> dis(-7.5f, 7.5f); // Define the range

		Enemy* enemy = new Enemy(mGame);
		enemy->transform.position = glm::vec3(dis(gen), 0.f, player->transform.position.z + 200.f);
		gameplayScene->AddGameObject(enemy);
		mSpawnedNew = true;
	}

	if (transform.position.z < player->transform.position.z -20.f)
		gameplayScene->RemoveGameObject(this);
}