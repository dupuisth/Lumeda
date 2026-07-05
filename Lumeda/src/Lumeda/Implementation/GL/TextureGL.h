#pragma once

#include <glm/glm.hpp>
#include <string>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/Texture.h>

namespace Lumeda
{
class LowLevelGraphicsGL;

class TextureGL : public iTexture
{
public:
  TextureGL(const tString& name, eTextureType type, eTextureUsage usage, iLowLevelGraphics& lowLevelGraphics);
  ~TextureGL();

  void Bind(unsigned int slot);

  void CreateFromRawData(const glm::ivec3& size, ePixelFormat pixelFormat, unsigned char* data) override;

  void SetWrapping(eTextureWrapping wrapping) override;
  void SetFiltering(eTextureFiltering filtering) override;

  bool HasData() { return m_HandleGL != 0; }
  unsigned int GetHandleGL() { return m_HandleGL; }

private:
  void CopyTextureDataToGL(unsigned char* data);
  void ApplyProperties();

private:
  unsigned int m_HandleGL;

  LowLevelGraphicsGL& m_LowLevelGraphicsGL;
};
} // namespace Lumeda