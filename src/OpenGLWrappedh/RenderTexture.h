#pragma once

#include <GL/glew.h>

#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

class RenderTexture
{
public:
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void bind();
	void unbind();
	GLuint getTextureId();

	int getWidth();
	int getHeight();

	void clear();

private:
	GLuint m_fboId;
	GLuint m_texId;
	GLuint m_rboId;

	int m_width;
	int m_height;
};
#endif // RENDERTEXTURE_H