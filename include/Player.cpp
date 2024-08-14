#include "Player.h"
#include "GameplayScene.h"

#include <glm/glm.hpp>
#include <random>
#include <cmath>
#include <iostream>

Player::Player(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Player;

	mShader = &(mGame->GetShaderLibrary()->objectShader);
	mModel = &(mGame->GetModelLibrary()->carModel);
	mTexture = &(mGame->GetModelLibrary()->playerTexture);

	// Figures come from testing model in Unity
	mBoundingBox.offset.y = 0.2f;
	mBoundingBox.offset.z = 0.54f;

	mBoundingBox.widthX = 3.2f;
	mBoundingBox.heightY = 1.7f;
	mBoundingBox.depthZ = 8.4f;

	std::random_device rd;  // Seed for the random number engine
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_real_distribution<> dis(360, 720); // Define the range

	int randomAngle = dis(gen);

	float mSpinDirection;

	if (randomAngle % 2 == 0)
	{
		mSpinDirection = 1.f;
	}
	else
	{
		mSpinDirection = -1.f;
	}

	mFinalRotation = randomAngle * mSpinDirection;
}

void Player::Update(float _deltaTime)
{
	GameplayScene* gameplayScene = dynamic_cast<GameplayScene*>(mGame->GetCurrentScene());

	if (gameplayScene->GetGameOver())
	{
		// Player is spinning

		float gameOverWaitTime = gameplayScene->GetGOWaitTime() - 1.f;
		mSpinTime += _deltaTime;

		float t = mSpinTime / gameOverWaitTime;
		t = glm::clamp(t, 0.f, 1.f);

		// Logarithmic interpolation for decreasing speed spin
		float aValue = glm::log(1.0f + mSpinK * t) / glm::log(1.0f + mSpinK);

		transform.rotation.y = glm::mix(0.f, mFinalRotation, aValue);

		return;
	}

	mHoverValue += mHoverSpeed * _deltaTime;
	float hoverHeight = sin(mHoverValue);
	transform.position.y = hoverHeight * 0.25f;

	if (mGame->keyPress[SDLK_a] || mGame->keyPress[SDLK_LEFT])
	{
		transform.position.x += mLRMoveSpeed * _deltaTime;
	}

	if (mGame->keyPress[SDLK_d] || mGame->keyPress[SDLK_RIGHT])
	{
		transform.position.x += -mLRMoveSpeed * _deltaTime;
	}

	if (mGame->keyPress[SDLK_w] || mGame->keyPress[SDLK_UP])
	{
		transform.position += transform.GetForward() * mFBMoveSpeed * _deltaTime;
	}

	if (mGame->keyPress[SDLK_s] || mGame->keyPress[SDLK_DOWN])
	{
		transform.position += -transform.GetForward() * mFBMoveSpeed * _deltaTime;
	}
}