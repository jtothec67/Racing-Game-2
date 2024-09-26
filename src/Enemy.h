#pragma once

#include "threeDObject.h"
#include "Game.h"

class Enemy : public threeDObject
{
public:
	Enemy(Game* _game);

	~Enemy() {}

	void Update(float _deltaTime) override;

private:
	float mHoverValue = 0.f;
	float mHoverSpeed = 3.f;

	bool mSpawnedNew = false;
};