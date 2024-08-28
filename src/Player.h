#pragma once

#include "threeDObject.h"
#include "Game.h"

class Player : public threeDObject
{
public:
	Player(Game* _game);

	~Player() {}

	void Update(float _deltaTime);

private:
	float mForwardMultiplier = 0.3f;
	float mBackwardsMultiplier = 0.3f;
	float mLRMoveSpeed = 10.f;

	float mHoverValue = 0.f;
	float mHoverSpeed = 3.f;

	float mSpinTime = 0.f;
	float mFinalRotation = 0.f;
	float mSpinK = 5.f;
};