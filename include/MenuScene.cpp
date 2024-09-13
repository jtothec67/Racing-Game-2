#include "MenuScene.h"
#include "UIObject.h"
#include "Button.h"
#include "Skybox.h"

#include <string>

MenuScene::MenuScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	CreateMenuButtons(windowWidth, windowHeight);
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(float _deltaTime)
{
	mGame->GetCamera()->transform.rotation.y -= 10.f * _deltaTime;

	if (!mInSettings)
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
					//mGame->ChangeScene(Scene::HowToPlay);
					//return;
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
					playButton->SetSelected(false);

					Button* htpButton = (Button*)(mNamedGameObjects["SettingsButton"]);
					htpButton->SetSelected(true);
					break;
				}
				case MenuOption::Settings:
				{
					mCurrentOption = MenuOption::Quit;

					Button* htpButton2 = (Button*)(mNamedGameObjects["SettingsButton"]);
					htpButton2->SetSelected(false);

					Button* quitButton2 = (Button*)(mNamedGameObjects["QuitButton"]);
					quitButton2->SetSelected(true);
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
					quitButton3->SetSelected(false);

					Button* htpButton3 = (Button*)mNamedGameObjects["HowToPlayButton"];
					htpButton3->SetSelected(true);
					break;
				}
				case MenuOption::Settings:
				{
					mCurrentOption = MenuOption::Play;

					Button* htpButton4 = (Button*)mNamedGameObjects["SettingsButton"];
					htpButton4->SetSelected(false);

					Button* playButton4 = (Button*)mNamedGameObjects["PlayButton"];
					playButton4->SetSelected(true);
					break;
				}
			}
		}
	}
	else
	{

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
	// Remove settings buttons

	Button* playButton = new Button(mGame);
	playButton->SetSelected(true);
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
	htpButton->SetTextScale(0.44f);
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
    // Remove menu buttons

    Button* vsyncButton = new Button(mGame);
    vsyncButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 5, 0);
    vsyncButton->SetAnchor(Anchor::TopCenter);
    vsyncButton->SetText("VSync");
    vsyncButton->SetTextScale(0.8f);
    AddGameObject(vsyncButton);
    mNamedGameObjects["VSyncButton"] = vsyncButton;

    Button* limitFPSButton = new Button(mGame);
    limitFPSButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 4, 0);
    limitFPSButton->SetAnchor(Anchor::Center);
    limitFPSButton->SetText("Limit FPS");
    limitFPSButton->SetTextScale(0.44f);
    AddGameObject(limitFPSButton);
    mNamedGameObjects["LimitFPSButton"] = limitFPSButton;

    Button* fpsLimitToButton = new Button(mGame);
    fpsLimitToButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 3, 0);
    fpsLimitToButton->SetAnchor(Anchor::BottomCenter);
    fpsLimitToButton->SetText("FPS Limit To");
    fpsLimitToButton->SetTextScale(0.8f);
    AddGameObject(fpsLimitToButton);
    mNamedGameObjects["FPSLimitToButton"] = fpsLimitToButton;

    Button* applyButton = new Button(mGame);
    applyButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6) * 2, 0);
    applyButton->SetAnchor(Anchor::TopCenter);
    applyButton->SetText("Apply");
    applyButton->SetTextScale(0.8f);
    AddGameObject(applyButton);
    mNamedGameObjects["ApplyButton"] = applyButton;

    Button* backButton = new Button(mGame);
    backButton->transform.position = glm::vec3(_windowWidth / 2, (_windowHeight / 6), 0);
    backButton->SetAnchor(Anchor::Center);
    backButton->SetText("Back");
    backButton->SetTextScale(0.44f);
    AddGameObject(backButton);
    mNamedGameObjects["BackButton"] = backButton;
}