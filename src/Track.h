#pragma once

#include "threeDObject.h"
#include "Game.h"

class Track : public threeDObject
{
public:
	Track(Game* _game);

	~Track() {}

	void Update(float _deltaTime) override;

private:
	float mSpeedDiff = 2.5f;
};