#include "RenderTexture.h"

#include <exception>

RenderTexture::RenderTexture(int _width, int _height)
	: m_fboId(0)
	, m_texId(0)
	, m_rboId(0)
{
	m_width = _width;
	m_height = _height;
}

RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers(1, &m_fboId);
	glDeleteTextures(1, &m_texId);
	glDeleteRenderbuffers(1, &m_rboId);
}

void RenderTexture::bind()
{
	if (!m_fboId)
	{
		glGenFramebuffers(1, &m_fboId);
		if (!m_fboId) throw std::exception();
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

		glGenTextures(1, &m_texId);
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);

		glGenRenderbuffers(1, &m_rboId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboId);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void RenderTexture::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint RenderTexture::getTextureId()
{
	if(!m_texId) throw std::exception();

	return m_texId;
}

int RenderTexture::getWidth()
{
	return m_width;
}

int RenderTexture::getHeight()
{
	return m_height;
}

void RenderTexture::clear()
{
	bind();

	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unbind();
}