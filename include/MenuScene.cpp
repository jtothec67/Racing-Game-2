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
	AddGameObject(playButton);

	Button* htpButton = new Button(mGame);
	htpButton->SetTexture(&(mGame->GetModelLibrary()->htpButTex));
	htpButton->SetSelectedTexture(&(mGame->GetModelLibrary()->htpButHoverTex));
	htpButton->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4) * 2, 0);
	AddGameObject(htpButton);

	Button* quitButton = new Button(mGame);
	quitButton->SetTexture(&(mGame->GetModelLibrary()->quitButTex));
	quitButton->SetSelectedTexture(&(mGame->GetModelLibrary()->quitButHoverTex));
	quitButton->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4), 0);
	AddGameObject(quitButton);

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
	else
	if(mGame->keyDown[SDLK_s])
	{
		switch (mCurrentOption)
		{
		case MenuOption::Play:
		{
			mCurrentOption = MenuOption::HowToPlay;
			Button* playButton = dynamic_cast<Button*>(mGameObjects[0]); // Accessing them directly because we know what they are (disgusting, think of better way. Could use the tag system but a tag per button doesn't seem right)
			playButton->SetSelected(false);

			Button* htpButton = dynamic_cast<Button*>(mGameObjects[1]);
			htpButton->SetSelected(true);
			break;
		}
		case MenuOption::HowToPlay:
		{
			mCurrentOption = MenuOption::Quit;

			Button* htpButton2 = dynamic_cast<Button*>(mGameObjects[1]);
			htpButton2->SetSelected(false);

			Button* quitButton2 = dynamic_cast<Button*>(mGameObjects[2]);
			quitButton2->SetSelected(true);
			break;
		}
		}
	}
	else if (mGame->keyDown[SDLK_w])
	{
		switch (mCurrentOption)
		{
		case MenuOption::Quit:
		{
			mCurrentOption = MenuOption::HowToPlay;

			Button* quitButton3 = (Button*)mGameObjects[2];
			quitButton3->SetSelected(false);

			Button* htpButton3 = (Button*)mGameObjects[1];
			htpButton3->SetSelected(true);
			break;
		}
		case MenuOption::HowToPlay:
		{
			mCurrentOption = MenuOption::Play;

			Button* htpButton4 = (Button*)mGameObjects[1];
			htpButton4->SetSelected(false);

			Button* playButton4 = (Button*)mGameObjects[0];
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
	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}
}