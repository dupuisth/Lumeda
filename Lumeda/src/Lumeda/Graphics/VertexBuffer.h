#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>

namespace Lumeda
{
class iLowLevelGraphics;

class iVertexBuffer
{
public:
  iVertexBuffer(iLowLevelGraphics& lowLevelGraphics) : m_LowLevelGraphics(lowLevelGraphics) {}
  virtual ~iVertexBuffer() = default;

  ///////////////////////////////////////////
  // Data
  ///////////////////////////////////////////
  virtual void
  SetData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<sVertexArrayAttrib>& attribs) = 0;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Drawing
  ///////////////////////////////////////////
  virtual void Draw() = 0;
  //---------------------------------------//

protected:
  iLowLevelGraphics& m_LowLevelGraphics;
};

} // namespace Lumeda