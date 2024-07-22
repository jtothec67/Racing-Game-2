#pragma once

#include <GL/glew.h>

#include <vector>
#include <string>

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture(const std::string& _path);
	Texture(const std::vector<std::string>& _facePaths);
	GLuint id();

	void GetSize(int& _width, int& _height) { _width = m_width; _height = m_height; }

private:
	GLuint m_id;

	int m_width;
	int m_height;
	bool m_dirty;

	bool skybox;

	std::vector<unsigned char> m_data;
	std::vector<std::string> m_syboxFaces;
};
#endif // TEXTURE_H