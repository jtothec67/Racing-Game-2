#include "OpenGLWrappedh/Shader.h"

#include <glm/ext.hpp>

#include <iostream>
#include <exception>
#include <fstream>

Shader::Shader(const std::string& _vertpath, const std::string& _fragpath)
	: m_id(0)
	, m_vertsrc()
	, m_fragsrc("")
{
	m_vertpath = _vertpath;
	m_fragpath = _fragpath;

	std::ifstream vfile(_vertpath);
	
	if (!vfile.is_open())
	{
		std::cout << "Couln't open shader: " << _vertpath << std::endl;
		throw std::exception();
	}
	
	std::string vline;
	
	while (!vfile.eof())
	{
		std::getline(vfile, vline);
		vline += "\n";
		m_vertsrc += vline;
	}


	std::ifstream lfile(_fragpath);

	if (!lfile.is_open())
	{
		std::cout << "Couln't open shader: " << _fragpath << std::endl;
		throw std::exception();
	}

	std::string lline;

	while (!lfile.eof())
	{
		std::getline(lfile, lline);
		lline += "\n";
		m_fragsrc += lline;
	}
	
	m_dirty = true;
}

GLuint Shader::id()
{
	if (m_fragsrc == "" || m_vertsrc == "")
	{
		throw std::exception();
	}
	if (m_dirty)
	{
		GLuint v_id = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* GLvertsrc = m_vertsrc.c_str();
		glShaderSource(v_id, 1, &GLvertsrc, NULL);
		glCompileShader(v_id);
		GLint success = 0;
		glGetShaderiv(v_id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			std::cout << "Shader failed to compile: " << m_vertpath << std::endl;
			throw std::exception();
		}


		GLuint f_id = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* GLfragsrc = m_fragsrc.c_str();
		glShaderSource(f_id, 1, &GLfragsrc, NULL);
		glCompileShader(f_id);
		glGetShaderiv(f_id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			std::cout << "Shader failed to compile: " << m_fragpath << std::endl;
			throw std::exception();
		}


		m_id = glCreateProgram();

		glAttachShader(m_id, v_id);
		glAttachShader(m_id, f_id);

		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		glDetachShader(m_id, v_id);
		glDeleteShader(v_id);
		glDetachShader(m_id, f_id);
		glDeleteShader(f_id);

		m_dirty = false;
	}

	return m_id;
}

void Shader::uniform(const std::string& _name, const glm::mat4& value)
{
	// Find uniform locations
	GLint loc = glGetUniformLocation(id(), _name.c_str());

	glUseProgram(id());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	glUseProgram(0);
}

void Shader::uniform(const std::string& _name, const glm::vec3& value)
{
	// Find uniform locations
	GLint loc = glGetUniformLocation(id(), _name.c_str());

	glUseProgram(id());
	glUniform3fv(loc, 1, glm::value_ptr(value));
	glUseProgram(0);
}

void Shader::draw(Model* _model, Texture* _tex)
{
	glUseProgram(id());
	glBindVertexArray(_model->vao_id());
	glBindTexture(GL_TEXTURE_2D, _tex->id());
	glDrawArrays(GL_TRIANGLES, 0, _model->vertex_count());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void Shader::draw(Mesh* _mesh, Texture* _tex)
{
	glUseProgram(id());
	glBindVertexArray(_mesh->id());
	glBindTexture(GL_TEXTURE_2D, _tex->id());
	glDrawArrays(GL_TRIANGLES, 0, _mesh->vertex_count());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void Shader::draw(Mesh& _mesh, Texture& _tex)
{
	glUseProgram(id());
	glBindVertexArray(_mesh.id());
	glBindTexture(GL_TEXTURE_2D, _tex.id());
	glDrawArrays(GL_TRIANGLES, 0, _mesh.vertex_count());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

void Shader::draw(Mesh& _mesh, GLuint _texId)
{
	glUseProgram(id());
	glBindVertexArray(_mesh.id());
	glBindTexture(GL_TEXTURE_2D, _texId);
	glDrawArrays(GL_TRIANGLES, 0, _mesh.vertex_count());
	glUseProgram(0);
}

void Shader::draw(Model& _model, Texture& _tex)
{
	glUseProgram(id());
	glBindVertexArray(_model.vao_id());
	glBindTexture(GL_TEXTURE_2D, _tex.id());
	glDrawArrays(GL_TRIANGLES, 0, _model.vertex_count());
	glUseProgram(0);
}

void Shader::draw(Model& _model, GLuint _texId)
{
	glUseProgram(id());
	glBindVertexArray(_model.vao_id());
	glBindTexture(GL_TEXTURE_2D, _texId);
	glDrawArrays(GL_TRIANGLES, 0, _model.vertex_count());
	glUseProgram(0);
}

void Shader::draw(Model& _model, Texture& _tex, RenderTexture& _renderTex)
{
	_renderTex.bind();

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glViewport(0, 0, _renderTex.getWidth(), _renderTex.getHeight());

	glUseProgram(id());
	glBindVertexArray(_model.vao_id());
	glBindTexture(GL_TEXTURE_2D, _tex.id());
	glDrawArrays(GL_TRIANGLES, 0, _model.vertex_count());
	glUseProgram(0);

	_renderTex.unbind();

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Shader::draw(Mesh& _mesh, Texture& _tex, RenderTexture& _renderTex)
{
	_renderTex.bind();

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glViewport(0, 0, _renderTex.getWidth(), _renderTex.getHeight());

	glUseProgram(id());
	glBindVertexArray(_mesh.id());
	glBindTexture(GL_TEXTURE_2D, _tex.id());
	glDrawArrays(GL_TRIANGLES, 0, _mesh.vertex_count());
	glUseProgram(0);

	_renderTex.unbind();

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Shader::drawSkybox(Mesh& _skyboxMesh, Texture& _tex)
{
	glUseProgram(id());
	glBindTexture(GL_TEXTURE_CUBE_MAP, _tex.id());
	GLuint textureLocation = glGetUniformLocation(id(), "uTexEnv");
	glUniform1i(textureLocation, 0);
	glBindVertexArray(_skyboxMesh.id());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}