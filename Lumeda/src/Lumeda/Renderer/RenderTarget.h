#pragma once

#include <Lumeda/Core/Base.h>
#include <glm/glm.hpp>

namespace Lumeda
{
class RenderTarget
{
  public:
    virtual ~RenderTarget() = default;

    virtual const std::string& GetName() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    virtual void SetSize(const glm::ivec2& size) = 0;
    virtual const glm::ivec2& GetSize() const = 0;
};
} // namespace Lumeda