#pragma once

#include "threeDObject.h"
#include "Game.h"

class Player : public threeDObject
{
public:
	Player(Game* _game);

	~Player() {}

	void Update(float _deltaTime) override;

private:
	float mFBMoveSpeed = 5.f;
	float mLRMoveSpeed = 5.f;

	float mHoverValue = 0.f;
	float mHoverSpeed = 3.f;
};