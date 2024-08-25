#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "RenderTexture.h"
#include "Font.h"

#include <GL/glew.h>

#include <string>

class Shader
{
public:
	Shader(const std::string& _vertpath, const std::string& _fragpath);
	GLuint id() { return m_id; }

	void uniform(const std::string& _name, const glm::mat4& value);
	void uniform(const std::string& _name, const glm::vec3& value);

	void draw(Model* _model, Texture* _tex);
	void draw(Mesh* _mesh, Texture* _tex);
	void draw(Mesh& _mesh, Texture& _tex);
	void draw(Mesh& _mesh, GLuint _texId);
	void draw(Model& _model, Texture& _tex);
	void draw(Model& _model, GLuint _texId);
	void draw(Model& _model, Texture& _tex, RenderTexture& _renderTex);
	void draw(Mesh& _mesh, Texture& _tex, RenderTexture& _renderTexId);
	void drawSkybox(Mesh& _skyboxMesh, Texture& _tex);
	void drawText(Mesh& _mesh, Font& _font, const std::string& _text, float _x, float _y, float _scale);

private:
	GLuint m_id = 0;

	std::string m_vertsrc;
	std::string m_fragsrc;
};