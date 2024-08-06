#include "Enemy.h"

#include <glm/glm.hpp>
#include <ctime>

Enemy::Enemy(Game* _game) : threeDObject(_game)
{
	mTag = Tag::Enemy;

	mShader = &(mGame->GetShaderLibrary()->objectShader);
	mModel = &(mGame->GetModelLibrary()->carModel);

	srand(time(NULL));
	mTexture = &(mGame->GetModelLibrary()->enemyCarTextures[rand() % mGame->GetModelLibrary()->enemyCarTextures.size()]);
}

void Enemy::Update(float _deltaTime)
{
	
}