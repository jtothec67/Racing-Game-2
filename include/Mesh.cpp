#include "Mesh.h"

Mesh::Mesh()
	: m_id(0)
	, m_vaoid(0)
	, m_vboid(0)
	, m_dirty(true)
{

}

void Mesh::add(Face& _face)
{
	m_faces.push_back(_face);
}

GLuint Mesh::id()
{
	if (m_dirty)
	{
		std::vector<GLfloat> data;

		for (int i = 0; i < m_faces.size(); i++)
		{
			data.push_back(m_faces[i].a.m_position.x);
			data.push_back(m_faces[i].a.m_position.y);
			data.push_back(m_faces[i].a.m_position.z);
			data.push_back(m_faces[i].a.m_texcoords.x);
			data.push_back(m_faces[i].a.m_texcoords.y);
			data.push_back(m_faces[i].a.m_normal.x);
			data.push_back(m_faces[i].a.m_normal.y);
			data.push_back(m_faces[i].a.m_normal.z);

			data.push_back(m_faces[i].b.m_position.x);
			data.push_back(m_faces[i].b.m_position.y);
			data.push_back(m_faces[i].b.m_position.z);
			data.push_back(m_faces[i].b.m_texcoords.x);
			data.push_back(m_faces[i].b.m_texcoords.y);
			data.push_back(m_faces[i].b.m_normal.x);
			data.push_back(m_faces[i].b.m_normal.y);
			data.push_back(m_faces[i].b.m_normal.z);

			data.push_back(m_faces[i].c.m_position.x);
			data.push_back(m_faces[i].c.m_position.y);
			data.push_back(m_faces[i].c.m_position.z);
			data.push_back(m_faces[i].c.m_texcoords.x);
			data.push_back(m_faces[i].c.m_texcoords.y);
			data.push_back(m_faces[i].c.m_normal.x);
			data.push_back(m_faces[i].c.m_normal.y);
			data.push_back(m_faces[i].c.m_normal.z);
		}

		// Create a new VBO on the GPU and bind it
		glGenBuffers(1, &m_vboid);

		if (!m_vboid)
		{
			throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vboid);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(m_vaoid);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboid);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(data.at(0)), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(data.at(0)), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(data.at(0)), (void*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_dirty = false;
	}

	return m_vaoid;
}

GLsizei Mesh::vertex_count() const
{
	return (GLsizei)m_faces.size() * 3;
}