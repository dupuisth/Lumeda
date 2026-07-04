#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class iRenderBuffer : public iResourceBase
{
public:
  iRenderBuffer(const tString& name) : iResourceBase(name, L"") {}
  virtual ~iRenderBuffer() = default;

  virtual void Bind() = 0;
  virtual void UnBind() = 0;

  virtual void SetStorage(const glm::vec2& size, ePixelFormat format) = 0;
};
} // namespace Lumeda