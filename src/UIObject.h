#pragma once

#include "GameObject.h"
#include "Game.h"

#ifndef UIOBJECT_H
#define UIOBJECT_H

class UIObject : public GameObject
{
public:
	UIObject(Game* _game);

	~UIObject() {}

	void Draw() override;

protected:
	int mWidth;
	int mHeight;
};

#endif // UIOBJECT_H