#pragma once

#include "UIObject.h"
#include "Text.h"

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

	void SetText(std::string _text) { mText.SetText(_text); }

	void SetTextScale(float _scale) { mText.transform.scale.x = _scale; mText.transform.scale.y = _scale; }

protected:
	Texture* mHoverTexture;

	Text mText;

	int mHoveredWidth = 0;
	int mHoveredHeight = 0;

	bool mHovered = false;
};