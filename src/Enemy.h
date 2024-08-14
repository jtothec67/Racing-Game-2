#pragma once

#include "threeDObject.h"
#include "Game.h"

#include <iostream>

class Enemy : public threeDObject
{
public:
	Enemy(Game* _game);

	~Enemy() {}

	void Update(float _deltaTime) override;

private:
	float mSpeed = 1.0f;

	float mHoverValue = 0.f;
	float mHoverSpeed = 3.f;

	bool mSpawnedNew = false;
};