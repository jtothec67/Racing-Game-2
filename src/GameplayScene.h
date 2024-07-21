#pragma once

#include "BaseScene.h"

class GameplayScene : public BaseScene
{
public:
	GameplayScene(Game* _game);
	~GameplayScene();

	void Update(float _deltaTime) override;
	void Draw() override;
};