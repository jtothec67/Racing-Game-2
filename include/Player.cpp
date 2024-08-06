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
	if (mGame->keyPress[SDLK_a] || mGame->keyPress[SDLK_LEFT])
	{
		transform.rotation.y += 40.f * _deltaTime;
	}

	if (mGame->keyPress[SDLK_d] || mGame->keyPress[SDLK_RIGHT])
	{
		transform.rotation.y -= 40.f * _deltaTime;
	}

    transform.position += transform.GetForward() * mSpeed * _deltaTime;
}