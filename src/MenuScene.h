#pragma once

#include "BaseScene.h"
#include "Timer.h"

class MenuScene : public BaseScene
{
public:
	MenuScene(Game* _game);
	~MenuScene();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void CreateMenuButtons(int _windowWidth, int _windowHeight);
	void CreateSettingsButtons(int _windowWidth, int _windowHeight);

	void UpdateMenuButtons();
	void UpdateSettingsButtons();

	enum class MenuOption
	{
		Play,
		Settings,
		Quit
	};

	enum class SettingsOption
	{
		VSync,
		LimitFPS,
		FPSLimitTo,
		Apply,
		Back
	};

	bool mInSettings = false;

	MenuOption mCurrentOption = MenuOption::Play;
	SettingsOption mCurrentSettingsOption = SettingsOption::VSync;

	bool mVSyncToApply = false;
	bool mLimitFPSToApply = false;
	int mFPSLimitToApply = 60;

	std::vector<int> mFPSOptions = { 30, 60, 75, 120, 144, 240, 360 };
	int mCurrentFPSOption = 1;

	Timer mDisplayFPS;
};