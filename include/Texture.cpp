#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <exception>



Texture::Texture(const std::string& _path)
	: m_id(0)
	, m_width(0)
	, m_height(0)
	, m_dirty(false)
	, skybox(false)
{
	unsigned char* data = stbi_load(_path.c_str(), &m_width, &m_height, NULL, 4);

	if (!data)
	{
		throw std::exception();
	}

	for (size_t i = 0; i < m_width * m_height * 4; ++i)
	{
		m_data.push_back(data[i]);
	}

	m_dirty = true;

	free(data);
}

// Overloaded constructor for a cubemap, used for a skybox (usually 6 faces/images)
Texture::Texture(const std::vector<std::string>& _facePaths)
	: m_id(0)
	, m_width(0)
	, m_height(0)
	, m_dirty(false)
	, skybox(true)
{
	m_syboxFaces = _facePaths;
	m_dirty = true;
}

GLuint Texture::id()
{
	if (!skybox)
	{
		if (!m_id)
		{
			glGenTextures(1, &m_id);

			if (!m_id)
			{
				throw std::exception();
			}
		}

		if (m_dirty)
		{
			glBindTexture(GL_TEXTURE_2D, m_id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_data.at(0));

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			m_dirty = false;
		}
	}
	else if (m_dirty)
	{
		glGenTextures(1, &m_id);

		if (!m_id)
		{
			throw std::exception();
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

		int width, height;
		for (unsigned int i = 0; i < m_syboxFaces.size(); i++)
		{
			unsigned char* data = stbi_load(m_syboxFaces[i].c_str(), &width, &height, NULL, 0);

			if (data)
			{
				std::vector<unsigned char> skyboxFaceData;

				for (size_t j = 0; j < width * height * 4; ++j)
				{
					skyboxFaceData.push_back(data[j]);
				}

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &skyboxFaceData.at(0));
				stbi_image_free(data);
			}
			else
			{
				throw std::exception();
				stbi_image_free(data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		m_dirty = false;
	}

	return m_id;
}