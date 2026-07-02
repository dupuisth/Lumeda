#include <glad/glad.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/VertexBufferGL.h>

using namespace Lumeda;

VertexBufferGL::~VertexBufferGL()
{
  if (m_Vao != BUFFER_NULL_VALUE)
  {
    glDeleteVertexArrays(1, &m_Vao);
  }
  if (m_Vbo != BUFFER_NULL_VALUE)
  {
    glDeleteBuffers(1, &m_Vbo);
  }
  if (m_Ebo != BUFFER_NULL_VALUE)
  {
    glDeleteBuffers(1, &m_Ebo);
  }
}

void VertexBufferGL::SetData(const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices,
    const std::vector<sVertexArrayAttrib>& attribs)
{
  m_Vertices = vertices;
  m_Indices = indices;
  m_Attribs = attribs;

  if (m_Vao == BUFFER_NULL_VALUE)
  {
    glGenVertexArrays(1, &m_Vao);
  }
  glBindVertexArray(m_Vao);

  if (m_Vbo == BUFFER_NULL_VALUE)
  {
    glGenBuffers(1, &m_Vbo);
  }
  glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  if (m_Ebo == BUFFER_NULL_VALUE)
  {
    glGenBuffers(1, &m_Ebo);
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

  // What happens when the previous attribs are not used ?
  // ex: (0, 1, 2) were used, and now we only have (0, 1)
  //     (2) would still be active...
  size_t stride = CalculateStride();
  size_t offset = 0;
  for (const auto& attrib : m_Attribs)
  {
    GLenum GLType = VertexAttribTypeToGLType(attrib.type);
    glVertexAttribPointer(attrib.location, attrib.length, GLType, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(attrib.location);

    offset += CalculateStride(attrib);
  }

  glBindVertexArray(BUFFER_NULL_VALUE);
  glBindBuffer(GL_ARRAY_BUFFER, BUFFER_NULL_VALUE);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BUFFER_NULL_VALUE);
}

void VertexBufferGL::Draw()
{
  glBindVertexArray(m_Vao);
  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(BUFFER_NULL_VALUE);
}

size_t VertexBufferGL::CalculateStride()
{
  size_t stride = 0;
  for (const auto& attrib : m_Attribs)
  {
    stride += CalculateStride(attrib);
  }
  return stride;
}

size_t VertexBufferGL::CalculateStride(const sVertexArrayAttrib& attrib)
{
  switch (attrib.type)
  {
  case eVertexAttribType_Float:
    return sizeof(float) * attrib.length;
  }

  LUMEDA_CORE_ERROR("The given type has no conversion!");
  return 0;
}