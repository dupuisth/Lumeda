#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/RenderBuffer.h>

namespace Lumeda
{
class RenderBufferGL : public iRenderBuffer
{
public:
  RenderBufferGL(const tString& name);
  ~RenderBufferGL();

  bool Reload() { return false; }
  void Unload() {}
  void Destroy() {}

  void Bind();
  void UnBind();

  void SetStorage(const glm::vec2& size, ePixelFormat format);

  unsigned int GetOpenGLHandle() { return m_Rbo; }

private:
  unsigned int m_Rbo;
};

} // namespace Lumeda