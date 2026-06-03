#pragma once

#include <Lumeda/Core/Base.h>
#include <glm/glm.hpp>
#include <string>

namespace Lumeda
{
enum class eTextureFiltering
{
    Nearest,
    Linear
};

enum class eTextureWrapping
{
    Repeat,
    Clamp
};

enum class eTextureFormat
{
    RGB,
    DepthStencil
};

class Texture
{
  public:
    virtual ~Texture() = default;

    virtual void Bind(int slot = 0) = 0;
    virtual void UnBind() = 0;

    virtual const std::string& GetName() const = 0;
};

class Texture2D : public Texture
{
  public:
    virtual ~Texture2D() = default;

    virtual eTextureWrapping GetWrapping() const = 0;
    virtual void SetWrapping(eTextureWrapping wrapping) = 0;

    virtual eTextureFiltering GetFiltering() const = 0;
    virtual void SetFiltering(eTextureFiltering filtering) = 0;

    virtual const glm::ivec2& GetSize() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};
} // namespace Lumeda