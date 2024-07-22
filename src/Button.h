#pragma once

#include "UIObject.h"

class Button : public UIObject
{
public:
	Button(Game* _game);

	~Button() {}

	void Draw() override;

	bool IsSelected() { return mSelected; }
	void SetSelected(bool _selected) { mSelected = _selected; }

	void SetSelectedTexture(Texture* _texture) { mSelectedTexture = _texture; }

protected:
	Texture* mSelectedTexture;

	bool mSelected = false;
};