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

	bool IsSelected() { return mSelected; }
	void SetSelected(bool _hovered) { mSelected = _hovered; }

	void SetSelectedTexture(Texture* _texture) { mSelectedTexture = _texture; mSelectedTexture->GetSize(mSelectedWidth, mSelectedHeight); }

	void SetText(std::string _text) { mText.SetText(_text); }
	void SetTextScale(float _scale) { mText.transform.scale.x = _scale; mText.transform.scale.y = _scale; }
	void SetTextColour(glm::vec3 _colour) { mText.SetColour(_colour); }

protected:
	Texture* mSelectedTexture;

	Text mText;

	int mSelectedWidth = 0;
	int mSelectedHeight = 0;

	bool mSelected = false;
};