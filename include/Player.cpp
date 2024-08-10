#include "Player.h"

#include <glm/glm.hpp>

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
}

void Player::Update(float _deltaTime)
{
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