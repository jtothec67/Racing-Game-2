#include "Text.h"

#include <sstream>
#include <iostream>

Text::Text(Game* _game) : UIObject(_game)
{
	mFont = &(mGame->GetModelLibrary()->testFont);
	mMesh = &(mGame->GetModelLibrary()->textMesh);
	mShader = &(mGame->GetShaderLibrary()->fontShader);
}

void Text::Draw()
{
	mGame->GetShaderLibrary()->fontShader.drawText(*mMesh, *mFont, mText, transform.position.x, transform.position.y, transform.scale.x, mColour);
}

void Text::Draw(int _x, int _y)
{
	float currentLineWidth = 0.0f;
	float widestLineWidth = 0.0f;

    float currentLineHeight = 0.0f;
    float totalHeight = 0.0f;

	int numLines = 1;

	std::string::const_iterator c;
	for (c = mText.begin(); c != mText.end(); c++)
	{
		Character* ch = mFont->GetCharacter(c);

		if (*c == '\n')
		{
			currentLineWidth = 0.0f;
            totalHeight += currentLineHeight + (1.1 * transform.scale.x);
			numLines++;
		}
		else
		{
			float h = ch->Size.y * transform.scale.x;

			if (ch->Size.y - ch->Bearing.y != 0) h -= (ch->Size.y - ch->Bearing.y) * transform.scale.x;

            if (currentLineHeight < ((ch->Size.y)) * 1.1 * transform.scale.x) currentLineHeight = h;

            float advance = (ch->Advance >> 6) * transform.scale.x;
            currentLineWidth += advance;
            
			if (currentLineWidth > widestLineWidth) widestLineWidth = currentLineWidth;
		}
	}

    if (totalHeight == 0.0f) totalHeight = currentLineHeight;

    //std::cout << "Total Height: " << totalHeight << " Widest width: " << widestLineWidth << std::endl;

    int centredX = _x + transform.position.x;
    int centredY = _y + transform.position.y;

	int xVal = centredX - (widestLineWidth / 2);
	int yVal = 0;
    // Only going to use scale in x
	if (numLines == 1)
	{
		yVal = centredY - (totalHeight / 2);
	}
	else
	{
		// y needs to offset because its the bottom left of first letter
		yVal = centredY - (totalHeight / 2);
	}
    

    //std::cout << "X: " << xVal << " Y: " << yVal << std::endl;

	mGame->GetShaderLibrary()->fontShader.drawText(*mMesh, *mFont, mText, xVal, yVal, transform.scale.x, mColour);
}