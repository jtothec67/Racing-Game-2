#pragma once

#include "BaseScene.h"

class MenuScene : public BaseScene
{
public:
	MenuScene(Game* _game);
	~MenuScene();

private:
	void Update(float _deltaTime) override;
	void Draw() override;
};