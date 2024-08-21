#include "OpenGLWrappedh/Shader.h"

#include <glm/ext.hpp>

#include <iostream>
#include <exception>
#include <fstream>

Shader::Shader(const std::string& _vertpath, const std::string& _fragpath)
{
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

	GLuint v_id = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* GLvertsrc = m_vertsrc.c_str();
	glShaderSource(v_id, 1, &GLvertsrc, NULL);
	glCompileShader(v_id);
	GLint success = 0;
	glGetShaderiv(v_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::cout << "Shader failed to compile: " << _vertpath << std::endl;
		throw std::exception();
	}


	GLuint f_id = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* GLfragsrc = m_fragsrc.c_str();
	glShaderSource(f_id, 1, &GLfragsrc, NULL);
	glCompileShader(f_id);
	glGetShaderiv(f_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		std::cout << "Shader failed to compile: " << _fragpath << std::endl;
		throw std::exception();
	}


	m_id = glCreateProgram();

	glAttachShader(m_id, v_id);
	glAttachShader(m_id, f_id);

	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		std::cout << "Shader id failed to be created: " << _vertpath << std::endl << _fragpath << std::endl;
		throw std::exception();
	}

	glDetachShader(m_id, v_id);
	glDeleteShader(v_id);
	glDetachShader(m_id, f_id);
	glDeleteShader(f_id);
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
	glUseProgram(0);
}

void Shader::drawText(Mesh& _mesh, Font& _font, const std::string& _text, float _x, float _y, float _scale, const glm::vec3& _color)
{
	glDisable(GL_DEPTH_TEST);
    
	float copyX = _x;

	glUseProgram(id());
	glUniform3f(glGetUniformLocation(id(), "textColor"), _color.x, _color.y, _color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_mesh.vao());

	// iterate through all characters
	std::string::const_iterator c;
	for (c = _text.begin(); c != _text.end(); c++)
	{
		Character* ch = _font.GetCharacter(c);

		if (*c == '\n')
		{
			_y -= ((ch->Size.y)) * 1.1 * _scale;
			_x = copyX;
		}
		else
		{

			float xpos = _x + ch->Bearing.x * _scale;
			float ypos = _y - (ch->Size.y - ch->Bearing.y) * _scale;

			float w = ch->Size.x * _scale;
			float h = ch->Size.y * _scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch->TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, _mesh.vbo());
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			_x += (ch->Advance >> 6) * _scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
	}
	
	/* --------------------------Failed attempt at getting width of mesh to help centre text--------------------------*/
	//GLint bufferSize;
	//glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	//// Allocate memory to store the vertex data
	//GLfloat* vertexData = new GLfloat[bufferSize / sizeof(GLfloat)];

	//// Retrieve the vertex data from the VBO
	//glGetBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, vertexData);

	//// Now you can access the vertex data stored in the vertexData array
 //   float meshWidth = 0.0f;
 //   for (int i = 0; i < _mesh.vertex_count(); i += 3)
 //   {
 //       glm::vec3 v0 = glm::vec3(reinterpret_cast<float*>(_mesh.id())[i * 3], reinterpret_cast<float*>(_mesh.id())[(i * 3) + 1], reinterpret_cast<float*>(_mesh.id())[(i * 3) + 2]);
 //       glm::vec3 v1 = glm::vec3(reinterpret_cast<float*>(_mesh.id())[(i + 1) * 3], reinterpret_cast<float*>(_mesh.id())[((i + 1) * 3) + 1], reinterpret_cast<float*>(_mesh.id())[((i + 1) * 3) + 2]);
 //       glm::vec3 v2 = glm::vec3(reinterpret_cast<float*>(_mesh.id())[(i + 2) * 3], reinterpret_cast<float*>(_mesh.id())[((i + 2) * 3) + 1], reinterpret_cast<float*>(_mesh.id())[((i + 2) * 3) + 2]);

 //       float triangleWidth = glm::length(v1 - v0) + glm::length(v2 - v1) + glm::length(v0 - v2);
 //       meshWidth = std::max(meshWidth, triangleWidth);
 //   }

	//_mesh.SetTextboxWidth(meshWidth);
	//std::cout << "Mesh width: " << meshWidth << std::endl;
	//
	//// Don't forget to delete the allocated memory
	//delete[] vertexData;

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	glEnable(GL_DEPTH_TEST);
}