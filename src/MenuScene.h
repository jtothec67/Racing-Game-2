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

	void CreateMenuButtons(int _windowWidth, int _windowHeight);
	void CreateSettingsButtons(int _windowWidth, int _windowHeight);

	enum class MenuOption
	{
		Play,
		Settings,
		Quit
	};

	bool mInSettings = false;

	MenuOption mCurrentOption = MenuOption::Play;
};