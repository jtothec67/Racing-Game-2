#include "MenuScene.h"
#include "UIObject.h"
#include "Button.h"
#include "Skybox.h"

#include <string>

MenuScene::MenuScene(Game* _game) : BaseScene(_game)
{
	mDisplayFPS.Start();

	AddGameObject(new Skybox(mGame));

	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	CreateMenuButtons(windowWidth, windowHeight);

	mVSyncToApply = mGame->GetWindow()->IsVSyncActive();
	mLimitFPSToApply = mGame->IsFPSLimited();
	mFPSLimitToApply = mGame->GetFPSLimit();

	for (int i = 0; i < mFPSOptions.size(); i++)
	{
		if (mFPSOptions[i] == mFPSLimitToApply)
		{
			mCurrentFPSOption = i;
			break;
		}
		else
		{
			mCurrentFPSOption++;
		}
	}

	Text* fpsText = new Text(mGame);
	fpsText->transform.position = glm::vec3(40.f, windowHeight - 20.f, 0.f);
	fpsText->SetColour(glm::vec3(0.f, 1.f, 0.f));
	fpsText->transform.scale.x = 0.2f;
	fpsText->SetAnchor(Anchor::TopLeft);
	AddGameObject(fpsText);
	mNamedGameObjects["FPSText"] = fpsText;
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(float _deltaTime)
{
	if (mDisplayFPS.GetElapsedSeconds() > 0.5f)
	{
		Text* fpsText = (Text*)mNamedGameObjects["FPSText"];
		fpsText->SetText(std::to_string((int)(1.f / _deltaTime)));

		mDisplayFPS.Start();
	}

	mGame->GetCamera()->transform.rotation.y -= 10.f * _deltaTime;

	if (!mInSettings)
	{
		UpdateMenuButtons();
	}
	else
	{
		UpdateSettingsButtons();
	}

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}

	mRemoveGameObjects();
}

void MenuScene::Draw()
{
	mGame->UseCamera(mGame->GetCamera());

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}
}

void MenuScene::CreateMenuButtons(int _windowWidth, int _windowHeight)
{
	RemoveGameObject(mNamedGameObjects["VSyncButton"]);
	RemoveGameObject(mNamedGameObjects["LimitFPSButton"]);
	RemoveGameObject(mNamedGameObjects["FPSLimitToButton"]);
	RemoveGameObject(mNamedGameObjects["ApplyButton"]);
	RemoveGameObject(mNamedGameObjects["BackButton"]);

	Button* playButton = new Button(mGame);
	playButton->SetHovered(true);
	playButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 4) * 3, 0);
	playButton->SetAnchor(Anchor::TopCenter);
	playButton->SetText("Play");
	playButton->SetTextScale(0.8f);
	AddGameObject(playButton);
	mNamedGameObjects["PlayButton"] = playButton;

	Button* htpButton = new Button(mGame);
	htpButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 4) * 2, 0);
	htpButton->SetAnchor(Anchor::Center);
	htpButton->SetText("Settings");
	htpButton->SetTextScale(0.45f);
	AddGameObject(htpButton);
	mNamedGameObjects["SettingsButton"] = htpButton;

	Button* quitButton = new Button(mGame);
	quitButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 4), 0);
	quitButton->SetAnchor(Anchor::BottomCenter);
	quitButton->SetText("Quit");
	quitButton->SetTextScale(0.8f);
	AddGameObject(quitButton);
	mNamedGameObjects["QuitButton"] = quitButton;
}

void MenuScene::CreateSettingsButtons(int _windowWidth, int _windowHeight)
{
	RemoveGameObject(mNamedGameObjects["PlayButton"]);
	RemoveGameObject(mNamedGameObjects["SettingsButton"]);
	RemoveGameObject(mNamedGameObjects["QuitButton"]);

    Button* vsyncButton = new Button(mGame);
	vsyncButton->SetHovered(true);
    vsyncButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 5, 0);
    vsyncButton->SetAnchor(Anchor::TopCenter);
	if (mVSyncToApply) vsyncButton->SetText(" VSync\n< Yes >");
	else vsyncButton->SetText(" VSync\n < No >");
    vsyncButton->SetTextScale(0.4f);
    AddGameObject(vsyncButton);
    mNamedGameObjects["VSyncButton"] = vsyncButton;

    Button* limitFPSButton = new Button(mGame);
    limitFPSButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 4, 0);
    limitFPSButton->SetAnchor(Anchor::Center);
	if (mLimitFPSToApply) limitFPSButton->SetText("Limit FPS\n < Yes >");
    else limitFPSButton->SetText("Limit FPS\n  < No >");
    limitFPSButton->SetTextScale(0.4f);
	if (mVSyncToApply) limitFPSButton->SetVisible(false);
    AddGameObject(limitFPSButton);
    mNamedGameObjects["LimitFPSButton"] = limitFPSButton;

    Button* fpsLimitToButton = new Button(mGame);
    fpsLimitToButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 3, 0);
    fpsLimitToButton->SetAnchor(Anchor::BottomCenter);
	fpsLimitToButton->SetText("FPS Limit\nTo <" + std::to_string(mFPSOptions[mCurrentFPSOption]) + ">");
    fpsLimitToButton->SetTextScale(0.4f);
	if (!mLimitFPSToApply || (mVSyncToApply && mLimitFPSToApply)) fpsLimitToButton->SetVisible(false);
    AddGameObject(fpsLimitToButton);
    mNamedGameObjects["FPSLimitToButton"] = fpsLimitToButton;

    Button* applyButton = new Button(mGame);
    applyButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 2, 0);
    applyButton->SetAnchor(Anchor::TopCenter);
    applyButton->SetText("Apply");
    applyButton->SetTextScale(0.7f);
    AddGameObject(applyButton);
    mNamedGameObjects["ApplyButton"] = applyButton;

    Button* backButton = new Button(mGame);
    backButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6), 0);
    backButton->SetAnchor(Anchor::Center);
    backButton->SetText("Back");
    backButton->SetTextScale(0.45f);
    AddGameObject(backButton);
    mNamedGameObjects["BackButton"] = backButton;
}

void MenuScene::UpdateMenuButtons()
{
	if (mGame->keyDown[SDLK_RETURN])
	{
		switch (mCurrentOption)
		{
			case MenuOption::Play:
			{
				mGame->ChangeScene(Scene::Game);
				return;
				break;
			}
			case MenuOption::Settings:
			{
				int windowWidth, windowHeight;
				mGame->GetWindowSize(windowWidth, windowHeight);
				CreateSettingsButtons(windowWidth, windowHeight);
				mInSettings = true;
				mCurrentOption = MenuOption::Play;
				break;
			}
			case MenuOption::Quit:
			{
				mGame->StopGameRunning();
				return;
				break;
			}
		}
	}

	if (mGame->keyDown[SDLK_s] || mGame->keyDown[SDLK_DOWN])
	{
		switch (mCurrentOption)
		{
			case MenuOption::Play:
			{
				mCurrentOption = MenuOption::Settings;
				Button* playButton = (Button*)(mNamedGameObjects["PlayButton"]);
				playButton->SetHovered(false);

				Button* htpButton = (Button*)(mNamedGameObjects["SettingsButton"]);
				htpButton->SetHovered(true);
				break;
			}
			case MenuOption::Settings:
			{
				mCurrentOption = MenuOption::Quit;

				Button* htpButton2 = (Button*)(mNamedGameObjects["SettingsButton"]);
				htpButton2->SetHovered(false);

				Button* quitButton2 = (Button*)(mNamedGameObjects["QuitButton"]);
				quitButton2->SetHovered(true);
				break;
			}
		}
	}

	if (mGame->keyDown[SDLK_w] || mGame->keyDown[SDLK_UP])
	{
		switch (mCurrentOption)
		{
			case MenuOption::Quit:
			{
				mCurrentOption = MenuOption::Settings;

				Button* quitButton3 = (Button*)mNamedGameObjects["QuitButton"];
				quitButton3->SetHovered(false);

				Button* htpButton3 = (Button*)mNamedGameObjects["SettingsButton"];
				htpButton3->SetHovered(true);
				break;
			}
			case MenuOption::Settings:
			{
				mCurrentOption = MenuOption::Play;

				Button* htpButton4 = (Button*)mNamedGameObjects["SettingsButton"];
				htpButton4->SetHovered(false);

				Button* playButton4 = (Button*)mNamedGameObjects["PlayButton"];
				playButton4->SetHovered(true);
				break;
			}
		}
	}
}

void MenuScene::UpdateSettingsButtons()
{
	if (mGame->keyDown[SDLK_RETURN])
	{
		switch (mCurrentSettingsOption)
		{
			case SettingsOption::Apply:
			{
				mGame->GetWindow()->ActivateVSync(mVSyncToApply);

				if (!mVSyncToApply)
				{
					mGame->SetFPSLimit(mFPSLimitToApply);

					if (mLimitFPSToApply)
					{
						mGame->LimitFPS(mFPSLimitToApply);
					}
				}

				break;
			}
			case SettingsOption::Back:
			{
				int windowWidth, windowHeight;
				mGame->GetWindowSize(windowWidth, windowHeight);
				CreateMenuButtons(windowWidth, windowHeight);
				mInSettings = false;
				mCurrentSettingsOption = SettingsOption::VSync;

				mVSyncToApply = mGame->GetWindow()->IsVSyncActive();
				mLimitFPSToApply = mGame->IsFPSLimited();
				mFPSLimitToApply = mGame->GetFPSLimit();

				for (int i = 0; i < mFPSOptions.size(); i++)
				{
					if (mFPSOptions[i] == mFPSLimitToApply)
					{
						mCurrentFPSOption = i;
						break;
					}
					else
					{
						mCurrentFPSOption++;
					}
				}

				break;
			}
		}
	}
	if (mGame->keyDown[SDLK_LEFT] || mGame->keyDown[SDLK_a])
	{
		switch (mCurrentSettingsOption)
		{
			case SettingsOption::VSync:
			{
				if (mVSyncToApply)
				{
					mVSyncToApply = false;
					Button* VSyncButton = (Button*)mNamedGameObjects["VSyncButton"];
					VSyncButton->SetText(" VSync\n < No >");

					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetVisible(true);

					if (mLimitFPSToApply)
					{
						Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
						fpsLimitToButton->SetVisible(true);
					}
				}
				else
				{
					mVSyncToApply = true;
					Button* VSyncButton = (Button*)mNamedGameObjects["VSyncButton"];
					VSyncButton->SetText(" VSync\n< Yes >");

					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetVisible(false);
					limitFPSButton->SetHovered(false);

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(false);
					fpsLimitToButton->SetHovered(false);
				}
				break;
			}
			case SettingsOption::LimitFPS:
			{
				if (mLimitFPSToApply)
				{
					mLimitFPSToApply = false;
					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetText("Limit FPS\n  < No >");

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(false);
					fpsLimitToButton->SetHovered(false);
				}
				else
				{
					mLimitFPSToApply = true;
					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetText("Limit FPS\n < Yes >");

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(true);
				}
				break;
			}
			case SettingsOption::FPSLimitTo:
			{
				mCurrentFPSOption--;
				if (mCurrentFPSOption < 0)
				{
					mCurrentFPSOption = mFPSOptions.size() - 1;
				}

				mFPSLimitToApply = mFPSOptions[mCurrentFPSOption];

				Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
				fpsLimitToButton->SetText("FPS Limit\nTo <" + std::to_string(mFPSLimitToApply) + ">");
				break;
			}
		}
	}

	if (mGame->keyDown[SDLK_RIGHT] || mGame->keyDown[SDLK_d])
	{
		switch (mCurrentSettingsOption)
		{
			case SettingsOption::VSync:
			{
				if (mVSyncToApply)
				{
					mVSyncToApply = false;
					Button* VSyncButton = (Button*)mNamedGameObjects["VSyncButton"];
					VSyncButton->SetText(" VSync\n < No >");

					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetVisible(true);

					if (mLimitFPSToApply)
					{
						Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
						fpsLimitToButton->SetVisible(true);
					}
				}
				else
				{
					mVSyncToApply = true;
					Button* VSyncButton = (Button*)mNamedGameObjects["VSyncButton"];
					VSyncButton->SetText(" VSync\n< Yes >");

					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetVisible(false);
					limitFPSButton->SetHovered(false);

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(false);
					fpsLimitToButton->SetHovered(false);
				}
				break;
			}
			case SettingsOption::LimitFPS:
			{
				if (mLimitFPSToApply)
				{
					mLimitFPSToApply = false;
					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetText("Limit FPS\n  < No >");

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(false);
					fpsLimitToButton->SetHovered(false);
				}
				else
				{
					mLimitFPSToApply = true;
					Button* limitFPSButton = (Button*)mNamedGameObjects["LimitFPSButton"];
					limitFPSButton->SetText("Limit FPS\n < Yes >");

					Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
					fpsLimitToButton->SetVisible(true);
				}
				break;
			}
			case SettingsOption::FPSLimitTo:
			{
				mCurrentFPSOption++;
				if (mCurrentFPSOption > mFPSOptions.size()-1)
				{
					mCurrentFPSOption = 0;
				}

				mFPSLimitToApply = mFPSOptions[mCurrentFPSOption];

				Button* fpsLimitToButton = (Button*)mNamedGameObjects["FPSLimitToButton"];
				fpsLimitToButton->SetText("FPS Limit\nTo <" + std::to_string(mFPSLimitToApply) + ">");
				break;
			}
		}
	}

	if (mGame->keyDown[SDLK_s] || mGame->keyDown[SDLK_DOWN])
	{
		switch (mCurrentSettingsOption)
		{
			case SettingsOption::VSync:
			{
				Button* vsyncButton = (Button*)(mNamedGameObjects["VSyncButton"]);
				vsyncButton->SetHovered(false);

				if (mVSyncToApply)
				{
					mCurrentSettingsOption = SettingsOption::Apply;

					Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
					applyButton->SetHovered(true);
				}
				else
				{
					mCurrentSettingsOption = SettingsOption::LimitFPS;

					Button* limitFPSButton = (Button*)(mNamedGameObjects["LimitFPSButton"]);
					limitFPSButton->SetHovered(true);
				}

				break;
			}
			case SettingsOption::LimitFPS:
			{
				Button* limitFPSButton = (Button*)(mNamedGameObjects["LimitFPSButton"]);
				limitFPSButton->SetHovered(false);

				if (mLimitFPSToApply)
				{
					mCurrentSettingsOption = SettingsOption::FPSLimitTo;

					Button* fpsLimitToButton = (Button*)(mNamedGameObjects["FPSLimitToButton"]);
					fpsLimitToButton->SetHovered(true);
				}
				else
				{
					mCurrentSettingsOption = SettingsOption::Apply;

					Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
					applyButton->SetHovered(true);
				}

				Button* fpsLimitToButton = (Button*)(mNamedGameObjects["FPSLimitToButton"]);
				fpsLimitToButton->SetHovered(true);
				break;
			}
			case SettingsOption::FPSLimitTo:
			{
				mCurrentSettingsOption = SettingsOption::Apply;

				Button* fpsLimitToButton = (Button*)(mNamedGameObjects["FPSLimitToButton"]);
				fpsLimitToButton->SetHovered(false);

				Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
				applyButton->SetHovered(true);
				break;
			}
			case SettingsOption::Apply:
			{
				mCurrentSettingsOption = SettingsOption::Back;

				Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
				applyButton->SetHovered(false);

				Button* backButton = (Button*)(mNamedGameObjects["BackButton"]);
				backButton->SetHovered(true);
				break;
			}
		}
	}

	if (mGame->keyDown[SDLK_w] || mGame->keyDown[SDLK_UP])
	{
		switch (mCurrentSettingsOption)
		{
			case SettingsOption::LimitFPS:
			{
				mCurrentSettingsOption = SettingsOption::VSync;

				Button* limitFPSButton = (Button*)(mNamedGameObjects["LimitFPSButton"]);
				limitFPSButton->SetHovered(false);

				Button* vsyncButton = (Button*)(mNamedGameObjects["VSyncButton"]);
				vsyncButton->SetHovered(true);
				break;
			}
			case SettingsOption::FPSLimitTo:
			{
				mCurrentSettingsOption = SettingsOption::LimitFPS;

				Button* fpsLimitToButton2 = (Button*)(mNamedGameObjects["FPSLimitToButton"]);
				fpsLimitToButton2->SetHovered(false);

				Button* limitFPSButton2 = (Button*)(mNamedGameObjects["LimitFPSButton"]);
				limitFPSButton2->SetHovered(true);
				break;
			}
			case SettingsOption::Apply:
			{
				Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
				applyButton->SetHovered(false);

				if (mVSyncToApply)
				{
					mCurrentSettingsOption = SettingsOption::VSync;

					Button* vsyncButton = (Button*)(mNamedGameObjects["VSyncButton"]);
					vsyncButton->SetHovered(true);
				}
				else if (mLimitFPSToApply)
				{
					mCurrentSettingsOption = SettingsOption::FPSLimitTo;

					Button* fpsLimitToButton = (Button*)(mNamedGameObjects["FPSLimitToButton"]);
					fpsLimitToButton->SetHovered(true);
				}
				else if (!mLimitFPSToApply)
				{
					mCurrentSettingsOption = SettingsOption::LimitFPS;

					Button* fpsLimitToButton = (Button*)(mNamedGameObjects["LimitFPSButton"]);
					fpsLimitToButton->SetHovered(true);
				}
				

				break;
			}
			case SettingsOption::Back:
			{
				mCurrentSettingsOption = SettingsOption::Apply;

				Button* backButton = (Button*)(mNamedGameObjects["BackButton"]);
				backButton->SetHovered(false);

				Button* applyButton = (Button*)(mNamedGameObjects["ApplyButton"]);
				applyButton->SetHovered(true);
				break;
			}
		}
	}
}