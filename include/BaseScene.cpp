#include "BaseScene.h"

#include <iostream>

BaseScene::BaseScene(Game* _game)
{
	mGame = _game;
}

BaseScene::~BaseScene()
{
    for (int i = 0; i < mGameObjects.size(); i++)
    {
        delete mGameObjects[i];
    }
    mGameObjects.clear();

    for (int i = 0; i < mGameObjectsToRemove.size(); i++)
    {
        delete mGameObjectsToRemove[i];
    }
    mGameObjectsToRemove.clear();
}

void BaseScene::mRemoveGameObjects()
{
    if (mGameObjectsToRemove.empty())
        return;

    for (auto* objToRemove : mGameObjectsToRemove)
    {
        for (auto it = mGameObjects.rbegin(); it != mGameObjects.rend(); ++it)
        {
            if (*it == objToRemove)
            {
                mGameObjects.erase((it + 1).base());
                break;
            }
        }
    }

    mGameObjectsToRemove.clear();
}

GameObject* BaseScene::FindGameObjectByTag(Tag _tag)
{
    // Returns the first instance of a GameObject with the tag in mGameObjects

	for (auto* obj : mGameObjects)
	{
		if (obj->GetTag() == _tag)
			return obj;
	}

	return nullptr;
}