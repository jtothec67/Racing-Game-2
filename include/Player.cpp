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
    glm::vec3 forwardDirection = transform.GetForward();
    transform.position += forwardDirection * mSpeed * _deltaTime;
}