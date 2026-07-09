#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceManager.h>

namespace Lumeda
{
class iTexture;
class Graphics;

class TextureManager : public iResourceManager<iTexture>
{
public:
  TextureManager(Resources& resources, Graphics& graphics) : iResourceManager(resources), m_Graphics(graphics) {}
  ~TextureManager() = default;

  iTexture* CreateTexture(const tString& name, eTextureType textureType, eTextureUsage usage = eTextureUsage_Normal);

private:
  Graphics& m_Graphics;
};
} // namespace Lumeda