#pragma once

#include "BaseScene.h"
#include "Timer.h"

class GameplayScene : public BaseScene
{
public:
	GameplayScene(Game* _game);
	~GameplayScene();

	void Update(float _deltaTime) override;
	void Draw() override;

	void SetMultiplier(float _multiplier) { mScoreMultiplier = _multiplier; }

	float GetGameSpeed() { return mGameSpeed; }
	bool GetGameOver() { return mGameOver; }
	float GetGOWaitTime() { return mGameOverWaitTime; }

	void Collision();

private:
	float mGameSpeed = 20.f; // Starting speed
	float mGameSpeedAccel = 2.f;

	float mScore = 0;
	float mScoreMultiplier = 1.f;

	float mGameOverDecelSpeed = 1.f; // Shouldn't get used as 1 but just in case
	float mGameOverWaitTime = 3.f; // Time for player to reach 0 speed after game over

	Timer mCrashTimer;

	bool mGameOver = false;
};