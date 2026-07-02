#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/VertexBuffer.h>

namespace Lumeda
{
class VertexBufferGL : public iVertexBuffer
{
public:
  VertexBufferGL(iLowLevelGraphics& lowLevelGraphics) :
      iVertexBuffer(lowLevelGraphics), m_Vao(BUFFER_NULL_VALUE), m_Vbo(BUFFER_NULL_VALUE), m_Ebo(BUFFER_NULL_VALUE)
  {
  }
  ~VertexBufferGL();

  ///////////////////////////////////////////
  // Data
  ///////////////////////////////////////////
  void SetData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<sVertexArrayAttrib>& attribs) override;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Drawing
  ///////////////////////////////////////////
  void Draw() override;
  //---------------------------------------//

private:
  size_t CalculateStride();
  size_t CalculateStride(const sVertexArrayAttrib& attrib);

private:
  std::vector<float> m_Vertices;
  std::vector<unsigned int> m_Indices;
  std::vector<sVertexArrayAttrib> m_Attribs;

  unsigned int m_Vao;
  unsigned int m_Vbo;
  unsigned int m_Ebo;

  const static unsigned int BUFFER_NULL_VALUE = 0;
};

} // namespace Lumeda