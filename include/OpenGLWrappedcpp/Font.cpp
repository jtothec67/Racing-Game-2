#include "OpenGLWrappedh/Font.h"

#include <iostream>
#include <exception>

Font::Font(const std::string& _fontPath)
{
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "Could not init FreeType Library" << std::endl;
        throw std::exception();
    }

    if (FT_New_Face(ft, _fontPath.c_str(), 0, &face))
    {
        std::cout << "Failed to load font: " << _fontPath << std::endl;
        throw std::exception();
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    mGenerateCharacterInformation();
}

void Font::mGenerateCharacterInformation()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph: " << (char)c << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
}

void Font::SetFontSize(int _size)
{
	fontSize = _size;
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	mGenerateCharacterInformation();
}