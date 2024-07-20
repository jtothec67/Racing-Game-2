#pragma once

#include "GameObject.h"

#include <vector>

class BaseScene
{
public:
	BaseScene(Game* _game, bool _isActive);
	virtual ~BaseScene();

	virtual void Update(float _deltaTime) {}
	virtual void Draw() {}

	virtual void RemoveGameObject(GameObject* _gameObject) { mGameObjectsToRemove.push_back(_gameObject); }

	virtual void AddGameObject(GameObject* _gameObject) { mGameObjects.push_back(_gameObject); }
	virtual const std::vector<GameObject*>* GetGameObjects() { return &mGameObjects; }

	glm::vec3 GetLightPos() { return mLightPos; }
	void SetLightPos(glm::vec3 _lightPos) { mLightPos = _lightPos; }

	void SetSceneActive(bool _sceneActive) { mSceneActive = _sceneActive; }
	bool IsSceneActive() { return mSceneActive; }

protected:
	void mRemoveGameObjects();

	Game* mGame;

	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mGameObjectsToRemove;

	glm::vec3 mLightPos = glm::vec3(0.f, 0.f, 0.f);

	bool mSceneActive;
};