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
	float mCurrentSpeed = 0.f;

	float mFBMultiplier = 0.3f;
	float mLRMoveSpeed = 10.f;

	float mHoverValue = 0.f;
	float mHoverSpeed = 3.f;

	float mSpinTime = 0.f;
	float mFinalRotation = 0.f;
	float mSpinK = 5.f;

	float mBaseFOV = 45.f;
	float mMaxFOVChange = 10.f;

	float mBaseMultiplier = 1.f;
	float mMaxMultiplierChange = 0.5f;
};