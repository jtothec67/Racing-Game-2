#include "MenuScene.h"
#include "UIObject.h"
#include "Button.h"
#include "Skybox.h"

MenuScene::MenuScene(Game* _game) : BaseScene(_game)
{
	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	Button* playButton = new Button(mGame);
	playButton->SetTexture(&(mGame->GetModelLibrary()->playButTex));
	playButton->SetSelectedTexture(&(mGame->GetModelLibrary()->playButHoverTex));
	playButton->SetSelected(true);
	playButton->transform.position = glm::vec3(windowWidth/2, (windowHeight / 4) * 3, 0);
	playButton->SetAnchor(Anchor::TopCentre);
	AddGameObject(playButton);
	mNamedGameObjects["PlayButton"] = playButton;

	Button* htpButton = new Button(mGame);
	htpButton->SetTexture(&(mGame->GetModelLibrary()->htpButTex));
	htpButton->SetSelectedTexture(&(mGame->GetModelLibrary()->htpButHoverTex));
	htpButton->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4) * 2, 0);
	htpButton->SetAnchor(Anchor::Centre);
	AddGameObject(htpButton);
	mNamedGameObjects["HowToPlayButton"] = htpButton;

	Button* quitButton = new Button(mGame);
	quitButton->SetTexture(&(mGame->GetModelLibrary()->quitButTex));
	quitButton->SetSelectedTexture(&(mGame->GetModelLibrary()->quitButHoverTex));
	quitButton->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4), 0);
	quitButton->SetAnchor(Anchor::BottomCentre);
	AddGameObject(quitButton);
	mNamedGameObjects["QuitButton"] = quitButton;

	mGame->GetWindow()->SetClearColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(float _deltaTime)
{
	if (mGame->keyDown[SDLK_RETURN])
	{
		switch (mCurrentOption)
		{
			case MenuOption::Play:
			{
				mGame->ChangeScene(Scene::Game);
				break;
			}
			case MenuOption::HowToPlay:
			{
				//mGame->ChangeScene(Scene::HowToPlay);
				break;
			}
			case MenuOption::Quit:
			{
				mGame->StopGameRunning();
				break;
			}
		}
	}
	
	if(mGame->keyDown[SDLK_s] || mGame->keyDown[SDLK_DOWN])
	{
		switch (mCurrentOption)
		{
			case MenuOption::Play:
			{
				mCurrentOption = MenuOption::HowToPlay;
				Button* playButton = (Button*)(mNamedGameObjects["PlayButton"]);
				playButton->SetSelected(false);

				Button* htpButton = (Button*)(mNamedGameObjects["HowToPlayButton"]);
				htpButton->SetSelected(true);
				break;
			}
			case MenuOption::HowToPlay:
			{
				mCurrentOption = MenuOption::Quit;

				Button* htpButton2 = (Button*)(mNamedGameObjects["HowToPlayButton"]);
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
				mCurrentOption = MenuOption::HowToPlay;

				Button* quitButton3 = (Button*)mNamedGameObjects["QuitButton"];
				quitButton3->SetSelected(false);

				Button* htpButton3 = (Button*)mNamedGameObjects["HowToPlayButton"];
				htpButton3->SetSelected(true);
				break;
			}
			case MenuOption::HowToPlay:
			{
				mCurrentOption = MenuOption::Play;

				Button* htpButton4 = (Button*)mNamedGameObjects["HowToPlayButton"];
				htpButton4->SetSelected(false);

				Button* playButton4 = (Button*)mNamedGameObjects["PlayButton"];
				playButton4->SetSelected(true);
				break;
			}
		}
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