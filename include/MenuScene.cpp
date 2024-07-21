#include "MenuScene.h"
#include "UIObject.h"
#include "Skybox.h"

MenuScene::MenuScene(Game* _game) : BaseScene(_game)
{
	AddGameObject(new Skybox(mGame));

	UIObject* test = new UIObject(mGame);
	test->SetTexture(&(mGame->GetModelLibrary()->playerTexture));
	AddGameObject(test);
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