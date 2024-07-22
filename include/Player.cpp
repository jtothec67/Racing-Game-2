#include "Player.h"

#include <glm/ext.hpp>

Player::Player(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Player;

	mShader = &(mGame->GetShaderLibrary()->objectShader);
	mModel = &(mGame->GetModelLibrary()->carModel);
	mTexture = &(mGame->GetModelLibrary()->playerTexture);

	transform.rotation.y = 90;

	transform.position.x = -50;
	transform.position.z = -50;
}

void Player::Update(float _deltaTime)
{
	transform.position.x += mSpeed * _deltaTime;
}