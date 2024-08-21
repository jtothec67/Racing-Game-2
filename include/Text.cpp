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
    //Split the text into lines
    std::vector<std::string> lines;
    std::string currentLine;
    std::istringstream stream(mText);
    while (std::getline(stream, currentLine, '\n')) {
        lines.push_back(currentLine);
    }

    // Find the length of the longest line
    int maxLength = 0;
    for (const auto& line : lines) {
        if (line.length() > maxLength) {
            maxLength = line.length();
        }
    }

    // Get the number of lines
    int numLines = lines.size();

    // Font size is 200 pixels heigh at 1 scale
    // 200 pixels is 3.5cm
    // 4 letters is 8.5cm (unless there's a long letter like w)
    // 1 letter is 2.125cm (2.1)
    // 2.1cm is 11.8 pixels

    int centredX = _x + transform.position.x;
    int centredY = _y + transform.position.y;

    // Only going to use scale in x
    int xVal = centredX - (maxLength * 38.f * transform.scale.x);
    int yVal = centredY +(((numLines * 100) - 155) * transform.scale.x);    // Not too sure tbh
                                                                            // Would be a lot easier if I could get the width/height of the mesh

	mGame->GetShaderLibrary()->fontShader.drawText(*mMesh, *mFont, mText, xVal, yVal, transform.scale.x, mColour);
}