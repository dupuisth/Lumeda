#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

class Texture2D;

enum eFramebufferAttachment
{
    ColorAttachment,
    DepthAttachment,
    StencilAttachment,
    DepthStencilAttachment
};

class Framebuffer
{
  public:
    virtual ~Framebuffer() = default;

    virtual const std::string& GetName() const = 0;

    virtual void Bind() = 0;
    virtual void UnBind() = 0;

    virtual void AttachTexture2D(eFramebufferAttachment slot, Texture2D* texture) = 0;
};
} // namespace Lumeda