#pragma once

#include <glm/ext.hpp>
#include <ft2build.h>
#include <GL/glew.h>

#include <string>
#include <map>

#include FT_FREETYPE_H  

struct Character {
	GLuint TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class Font
{
public:
	Font(const std::string& _fontPath);
	~Font() { }//FT_Done_Face(face); FT_Done_FreeType(ft); }

	void SetFontSize(int _size);
	int GetFontSize() { return fontSize; }

	Character* GetCharacter(std::string::const_iterator _c) { return &Characters[*_c]; }

private:
	void mGenerateCharacterInformation();

	FT_Library ft;
	FT_Face face;

	int fontSize = 200; // Height in pixels

	std::map<char, Character> Characters;
};