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

	float GetGameSpeed() { return mGameSpeed; }
	bool IsGameEnding() { return mGameEnding; }
	bool IsGameStarting() { return mGameStarting; }
	float GetGameEndingWaitTime() { return mGameEndingWaitTime; }

	void SetMultiplier(float _multiplier) { mScoreMultiplier = _multiplier; }

	void Collision();

private:
	void InitialiseSceneObjects();

	float mStartGameSpeed = 35.f; // Starting speed
	float mGameSpeedAccel = 2.f;

	float mGameSpeed = 0.f;

	float mScore = 0.f;
	float mScoreMultiplier = 1.f;

	float mGameEndingDecelSpeed = 1.f; // Shouldn't get used as 1 but just in case
	float mGameEndingWaitTime = 3.f; // Time for player to reach 0 speed after game over

	Timer mStartTimer;
	Timer mCrashTimer;

	bool mGameStarting = true;
	bool mGameEnding = false;

	Timer mDisplayFPS;
};