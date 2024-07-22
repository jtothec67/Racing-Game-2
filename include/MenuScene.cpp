#include "MenuScene.h"
#include "UIObject.h"
#include "Button.h"
#include "Skybox.h"

MenuScene::MenuScene(Game* _game) : BaseScene(_game)
{
	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);

	AddGameObject(new Skybox(mGame));

	Button* test = new Button(mGame);
	test->transform.position = glm::vec3(windowWidth/2, (windowHeight / 4) * 3, 0);
	AddGameObject(test);

	Button* test2 = new Button(mGame);
	test2->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4) * 2, 0);
	AddGameObject(test2);

	Button* test3 = new Button(mGame);
	test3->transform.position = glm::vec3(windowWidth / 2, (windowHeight / 4), 0);
	AddGameObject(test3);
}

MenuScene::~MenuScene()
{
	
}

void MenuScene::Update(float _deltaTime)
{
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