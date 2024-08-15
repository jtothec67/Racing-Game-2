#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

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
	Mesh(bool _skybox); // If mesh constructor called with true, it will create a skybox mesh

	void add(Face& _face);
	GLuint id();
	GLsizei vertex_count() const;

	bool IsSkybox() { return m_skybox; }


private:
	GLuint m_id = 0;

	GLuint m_vaoid = 0;
	GLuint m_vboid = 0;

	bool m_dirty = true;
	bool m_skybox = false;

	std::vector<Face> m_faces;
};