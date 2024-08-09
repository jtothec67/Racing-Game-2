#pragma once

#include "GameObject.h"

#include <vector>
#include <unordered_map>
#include <string>

class BaseScene
{
public:
	BaseScene(Game* _game);
	virtual ~BaseScene();

	virtual void Update(float _deltaTime) = 0;
	virtual void Draw() = 0;

	void RemoveGameObject(GameObject* _gameObject) { mGameObjectsToRemove.push_back(_gameObject); }

	void AddGameObject(GameObject* _gameObject) { mGameObjects.push_back(_gameObject); }
	const std::vector<GameObject*>* GetGameObjects() { return &mGameObjects; }

	glm::vec3 GetLightPos() { return mLightPos; }
	void SetLightPos(glm::vec3 _lightPos) { mLightPos = _lightPos; }

	GameObject* FindGameObjectByTag(Tag _tag);

	GameObject* GetPlayer() { return mNamedGameObjects["Player"]; }

protected:
	void mRemoveGameObjects();

	Game* mGame;

	std::unordered_map<std::string, GameObject*> mNamedGameObjects;
	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mGameObjectsToRemove;

	glm::vec3 mLightPos = glm::vec3(0.f, 20.f, 0.f);
};