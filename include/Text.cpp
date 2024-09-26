#include "Text.h"

#include <sstream>

Text::Text(Game* _game) : UIObject(_game)
{
	mFont = mGame->GetModelLibrary()->testFont;
	mMesh = mGame->GetModelLibrary()->textMesh;
	mShader = mGame->GetShaderLibrary()->fontShader;
}

void Text::Draw()
{
	if (mText == "")
		return;

	if (mText != mLastText || transform.scale.x != mLastScale)
	{
		mLastText = mText;
		mLastScale = transform.scale.x;

		float currentLineWidth = 0.0f;
		float widestLineWidth = 0.0f;

		float currentLineHeight = 0.0f;
		float totalHeight = 0.0f;

		bool firstLine = true;

		int numLines = 1;

		std::string::const_iterator c;
		for (c = mText.begin(); c != mText.end(); c++)
		{
			Character* ch = mFont->GetCharacter(c);

			if (*c == '\n')
			{
				firstLine = false;
				currentLineWidth = 0.0f;
				totalHeight += currentLineHeight;
				numLines++;
			}
			else
			{
				// Top to bottom of letter
				float height = ch->Size.y * transform.scale.x;

				// If multiple lines, encounter for spacing
				if (!firstLine)
					height = ch->Size.y * 1.3 * transform.scale.x; // 1.3 IS NEWLINE SPACING, NEEDS TO BE CHANGED IN SHADER.CPP TOO

				// If letter goes below the line
				if (ch->Size.y - ch->Bearing.y != 0)
					// Disregard below line
					height -= (ch->Size.y - ch->Bearing.y) * transform.scale.x;

				// Update height if letter is taller than current line height
				if (currentLineHeight < ch->Size.y * 1.3 * transform.scale.x)
					currentLineHeight = height;

				// Add only width if at the end of line, else add advance (includes spacing)
				if (*c == '\n' || std::next(c) == mText.end())
					currentLineWidth += ch->Size.x * transform.scale.x;
				else
					currentLineWidth += (ch->Advance >> 6) * transform.scale.x;

				if (currentLineWidth > widestLineWidth)
					widestLineWidth = currentLineWidth;
			}
		}

		if (numLines == 1)
			totalHeight = currentLineHeight;

		mXPos = transform.position.x - (widestLineWidth / 2);
		mYPos = 0;

		// Only going to use scale in x
		if (numLines == 1)
		{
			mYPos = transform.position.y - (totalHeight / 2);
		}
		else
		{
			float averageHeight = totalHeight / numLines;
			mYPos = transform.position.y + (((numLines - 2) * 0.75) * averageHeight) + (averageHeight / 2);
			// Not too sure how this works but took me a while to figure out.
			// Still slightly off but it's close enough.
		}
	}
	
	// Contemplated creating a "GetUniform" function to check if we actually need to update the uniform,
	// but that is apparently more expensive than just setting a uniform.
	// (Unable to use an mLastColour as this text might be the same colour but another text has changed the uniform to it's own colour)
	mShader->uniform("u_TextColour", mColour);
	mShader->drawText(*mMesh, *mFont, mText, mXPos, mYPos, transform.scale.x);
}

void Text::Draw(int _x, int _y)
{
	if (mText == "")
		return;

	if (mText != mLastText || transform.scale.x != mLastScale || _x != mLast_x || _y != mLast_y)
	{
		mLastText = mText;
		mLastScale = transform.scale.x;
		mLast_x = _x;
		mLast_y = _y;

		float currentLineWidth = 0.0f;
		float widestLineWidth = 0.0f;

		float currentLineHeight = 0.0f;
		float totalHeight = 0.0f;

		bool firstLine = true;

		// float so we can /2 later
		float numLines = 1.f;

		std::string::const_iterator c;
		for (c = mText.begin(); c != mText.end(); c++)
		{
			Character* ch = mFont->GetCharacter(c);

			if (*c == '\n')
			{
				firstLine = false;
				currentLineWidth = 0.0f;
				totalHeight += currentLineHeight;
				numLines++;
			}
			else
			{
				// Top to bottom of letter
				float height = ch->Size.y * transform.scale.x;

				// If multiple lines, encounter for spacing
				if (!firstLine)
					height = ch->Size.y * 1.3 * transform.scale.x; // 1.3 IS NEW LINE SPACING, NEEDS TO BE CHANGED IN SHADER.CPP TOO

				// If letter goes below the line
				if (ch->Size.y - ch->Bearing.y != 0)
					// Disregard below line
					height -= (ch->Size.y - ch->Bearing.y) * transform.scale.x;

				// Update height if letter is taller than current line height
				if (currentLineHeight < ch->Size.y * 1.3 * transform.scale.x)
					currentLineHeight = height;

				// Add only width if at the end of line, else add advance (includes spacing)
				if (*c == '\n' || std::next(c) == mText.end())
					currentLineWidth += ch->Size.x * transform.scale.x;
				else
					currentLineWidth += (ch->Advance >> 6) * transform.scale.x;

				if (currentLineWidth > widestLineWidth)
					widestLineWidth = currentLineWidth;
			}
		}

		if (numLines == 1)
			totalHeight = currentLineHeight;

		int centredX = _x + transform.position.x;
		int centredY = _y + transform.position.y;

		mXPos = centredX - (widestLineWidth / 2);
		mYPos = 0;

		// Only going to use scale in x
		if (numLines == 1)
		{
			mYPos = centredY - (totalHeight / 2);
		}
		else
		{
			float averageHeight = totalHeight / numLines;
			mYPos = centredY + (((numLines - 2) * 0.75) * averageHeight) + (averageHeight / 2);
			// Not too sure how this works but took me a while to figure out.
			// Still slightly off but it's close enough.
		}
	}

	mShader->uniform("u_TextColour", mColour);
	mShader->drawText(*mMesh, *mFont, mText, mXPos, mYPos, transform.scale.x);
}