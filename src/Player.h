#pragma once

#include "GameObject.h"
#include "Game.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameObject
{
public:
	Player(Game* _game);

	~Player() {}

	void Update(float _deltaTime) override;
	void Draw() override;

	void SetSpeed(float _speed) { mSpeed = _speed; }
	float GetSpeed() { return mSpeed; }

private:
	float mSpeed = 5.0f;
};

#endif // PLAYER_H