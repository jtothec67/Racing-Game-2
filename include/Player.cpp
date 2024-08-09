#include "Player.h"

#include <glm/glm.hpp>

Player::Player(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Player;

	mShader = &(mGame->GetShaderLibrary()->objectShader);
	mModel = &(mGame->GetModelLibrary()->carModel);
	mTexture = &(mGame->GetModelLibrary()->playerTexture);
}

void Player::Update(float _deltaTime)
{
	mHoverValue += mHoverSpeed * _deltaTime;
	float hoverHeight = sin(mHoverValue);
	transform.position.y = hoverHeight * 0.25f;

	if (mGame->keyPress[SDLK_a] || mGame->keyPress[SDLK_LEFT])
	{
		//transform.rotation.y += 40.f * _deltaTime;
		transform.position.x += mLRMoveSpeed * _deltaTime;
	}

	if (mGame->keyPress[SDLK_d] || mGame->keyPress[SDLK_RIGHT])
	{
		//transform.rotation.y -= 40.f * _deltaTime;
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