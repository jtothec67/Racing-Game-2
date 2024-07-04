#pragma once

#include "threeDObject.h"
#include "Game.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public threeDObject
{
public:
	Player(Game* _game);

	~Player() {}

	void Update(float _deltaTime) override;

	void SetSpeed(float _speed) { mSpeed = _speed; }
	float GetSpeed() { return mSpeed; }

private:
	float mSpeed = 5.0f;
};

#endif // PLAYER_H