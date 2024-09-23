#include "Track.h"
#include "GameplayScene.h"

#include <iostream>

Track::Track(Game* _game) : threeDObject(_game)
{
	mModel = mGame->GetModelLibrary()->trackModel;
	mTexture = mGame->GetModelLibrary()->trackAndGrassTexture;

	transform.position = glm::vec3(0.f, -2.f, 0.f);
	transform.scale = glm::vec3(0.02f, 0.06f, 0.1f);

	SetSpecular(false);
}

void Track::Update(float _deltaTime)
{
	GameplayScene* gameplayScene = (GameplayScene*)mGame->GetCurrentScene();

	if (transform.position.z <= gameplayScene->GetPlayer()->transform.position.z - GetLength())
	{
		gameplayScene->RemoveGameObject(this);

		Track* track = new Track(mGame);
		track->transform.position.z = transform.position.z + (3 * GetLength());
		//track->transform.position.z -= gameplayScene->GetGameSpeed() * mSpeedDiff * _deltaTime;
		gameplayScene->AddGameObject(track);
	}

	transform.position.z -= gameplayScene->GetGameSpeed() * mSpeedDiff * _deltaTime;
}