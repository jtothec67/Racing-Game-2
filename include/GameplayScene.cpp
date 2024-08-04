#include "GameplayScene.h"
#include "Player.h"
#include "Skybox.h"

GameplayScene::GameplayScene(Game* _game) : BaseScene(_game)
{
	mGame->GetCamera()->transform.position = glm::vec3(0.f, 10.f, 0.f);
	mGame->GetCamera()->transform.rotation = glm::vec3(-20.f, 0.f, 0.f);

	AddGameObject(new Skybox(mGame));

	Player* player = new Player(mGame);
	player->transform.position = glm::vec3(0.f, 0.f, -15.f);
	player->transform.rotation = glm::vec3(0.f, 180.f, 0.f);

	AddGameObject(player);
	mNamedGameObjects["Player"] = player;
}

GameplayScene::~GameplayScene()
{
	
}

void GameplayScene::Update(float _deltaTime)
{
	if (mGame->keyPress[SDLK_a])
	{
		mNamedGameObjects["Player"]->transform.rotation.y += 20.f * _deltaTime;
	}

	if (mGame->keyPress[SDLK_d])
	{
		mNamedGameObjects["Player"]->transform.rotation.y -= 20.f * _deltaTime;
	}

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Update(_deltaTime);
	}

	mRemoveGameObjects();
}

void GameplayScene::Draw()
{
	mGame->UseCamera(mGame->GetCamera());

	for (int i = 0; i < mGameObjects.size(); i++)
	{
		mGameObjects[i]->Draw();
	}
}