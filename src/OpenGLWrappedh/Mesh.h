#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>
#include <string>

struct Vertex
{
	glm::vec3 m_position;
	glm::vec2 m_texcoords;
	glm::vec3 m_normal;
};

struct Face
{
	Vertex a;
	Vertex b;
	Vertex c;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::string _meshType); // User specifies mesh type, is not one we know we make a normal mesh

	void add(Face& _face);
	GLuint id(); // Returns vao id + initialises mesh if dirty
	GLsizei vertex_count() const;

	GLuint vao() { return m_vaoid; }
	GLuint vbo() { return m_vboid; } // May need to pass using reference

	bool IsSkybox() { return m_skybox; }
	bool IsText() { return m_text; }

	void SetTextboxWidth(float _width) { textbox_width = _width; }
	float GetTextboxWidth() { return textbox_width; }

private:
	GLuint m_vaoid = 0;
	GLuint m_vboid = 0;

	bool m_dirty = true;

	bool m_skybox = false;
	bool m_text = false;

	float textbox_width = 0.0f;

	std::vector<Face> m_faces;
};