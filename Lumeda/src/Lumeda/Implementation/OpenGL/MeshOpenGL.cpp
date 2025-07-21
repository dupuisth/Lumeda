#include <Lumeda/Implementation/OpenGL/MeshOpenGL.h>

#include <glad/glad.h>

using namespace Lumeda;

static GLenum MeshAttribTypeToGLenum(MeshAttribType type)
{
	switch (type)
	{
	case Lumeda::MeshAttribType::INT:
		return GL_INT;
	case Lumeda::MeshAttribType::FLOAT:
		return GL_FLOAT;
	default:
		// Did not find a proper way to log the type..
		LUMEDA_CORE_ERROR("The given type have no conversion into OpenGL");
		throw std::runtime_error("The given type have no conversion into OpenGL");
	}
}

static size_t CalculateStride(const MeshAttrib& attrib)
{
	switch (attrib.Type)
	{
	case Lumeda::MeshAttribType::INT:
		return sizeof(int) * attrib.Count;
	case Lumeda::MeshAttribType::FLOAT:
		return sizeof(float) * attrib.Count;
	default:
		// Did not find a proper way to log the type..
		LUMEDA_CORE_ERROR("The given type have no conversion into OpenGL");
		throw std::runtime_error("The given type have no conversion into OpenGL"); 
	}
}

static size_t CalculateStride(const std::vector<MeshAttrib>& attribs)
{
	size_t stride = 0;
	for (size_t i = 0; i < attribs.size(); i++)
	{
		stride += CalculateStride(attribs[i]);
	}
	return stride;
}

MeshOpenGL::MeshOpenGL(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs)
	: m_Vertices(vertices), m_Indices(indices), m_Name(name), m_Attribs(attribs)
{
	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_Ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	size_t stride = CalculateStride(m_Attribs);
	size_t offset = 0;
	for (size_t i = 0; i < m_Attribs.size(); i++)
	{
		GLenum type = MeshAttribTypeToGLenum(m_Attribs[i].Type);
		glVertexAttribPointer(m_Attribs[i].Index, m_Attribs[i].Count, type, GL_FALSE, stride, (void*)(offset));
		glEnableVertexAttribArray(m_Attribs[i].Index);

		offset += CalculateStride(m_Attribs[i]);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshOpenGL::~MeshOpenGL()
{
	glDeleteVertexArrays(1, &m_Vao);
	glDeleteBuffers(1, &m_Vbo);
	glDeleteBuffers(1, &m_Ebo);
}

void MeshOpenGL::Draw()
{
	glBindVertexArray(m_Vao);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

const std::string& MeshOpenGL::GetName() const
{
	return m_Name;
}

