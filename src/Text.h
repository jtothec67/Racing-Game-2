#pragma once

#include "UIObject.h"
#include "OpenGLWrappedh/Font.h"

class Text : public UIObject
{
public:
	Text(Game* _game);
	~Text() {}

	void Draw() override;
	void Draw(int _x, int _y);

	void SetText(std::string _text) { mText = _text; }
	std::string GetText() { return mText; }

	void SetColour(glm::vec3 _colour) { mColour = _colour; }

private:
	Font* mFont;

	std::string mText = "";

	glm::vec3 mColour = glm::vec3(0.0f, 0.0f, 0.0f);

	float mXPos = 0.0f;
	float mYPos = 0.0f;

	// For checking if we need to do maths again
	std::string mLastText = "";
	float mLastScale = 0.0f;
	int mLast_x = 0;
	int mLast_y = 0;
};