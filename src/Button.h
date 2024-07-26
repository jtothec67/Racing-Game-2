#pragma once

#include "UIObject.h"

#include <iostream>

class Button : public UIObject
{
public:
	Button(Game* _game);

	~Button() {}

	void Draw() override;

	bool IsSelected() { return mHovered; }
	void SetSelected(bool _hovered) { mHovered = _hovered; }

	void SetSelectedTexture(Texture* _texture) { mHoverTexture = _texture; mHoverTexture->GetSize(mHoveredWidth, mHoveredHeight); }

protected:
	Texture* mHoverTexture;
	int mHoveredWidth = 0;
	int mHoveredHeight = 0;

	bool mHovered = false;
};