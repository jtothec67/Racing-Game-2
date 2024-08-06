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
	float mSpeed = 1.0f;
};