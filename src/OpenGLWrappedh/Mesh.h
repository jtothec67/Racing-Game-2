#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

#ifndef MESH_H
#define MESH_H

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


private:
	GLuint m_id;

	GLuint m_vaoid;
	GLuint m_vboid;

	bool m_dirty;
	bool m_skybox;

	std::vector<Face> m_faces;
};
#endif // MESH_H