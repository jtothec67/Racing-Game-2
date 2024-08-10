#pragma once

#include "BaseScene.h"

class GameplayScene : public BaseScene
{
public:
	GameplayScene(Game* _game);
	~GameplayScene();

	void Update(float _deltaTime) override;
	void Draw() override;

	float GetGameSpeed() { return mGameSpeed; }

	void Collision();

private:
	float mGameSpeed = 10.f;
	float mGameSpeedAccel = 1.f;
};