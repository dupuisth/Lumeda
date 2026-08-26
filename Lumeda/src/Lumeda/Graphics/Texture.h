#pragma once

#include <glm/glm.hpp>
#include <string>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class iLowLevelGraphics;

class iTexture : public iResourceBase
{
public:
  iTexture(const tString& name, eTextureType type, eTextureUsage usage, iLowLevelGraphics& lowLevelGraphics) :
      m_Type(type),
      m_Usage(usage),
      m_LowLevelGraphics(lowLevelGraphics),
      iResourceBase(name, _W("")),
      m_Filtering(eTextureFiltering_Linear),
      m_Wrapping(eTextureWrapping_Clamp)
  {
  }
  virtual ~iTexture() = default;

  bool Reload() { return false; }
  void Unload() {}
  void Destroy() {}
  virtual void Bind(unsigned int slot) = 0;

  virtual void CreateFromRawData(const glm::ivec3& size, ePixelFormat pixelFormat, unsigned char* data) = 0;
  virtual void CreateFromFile(const twString& path) = 0;

  eTextureUsage GetUsage() const { return m_Usage; }
  eTextureType GetType() const { return m_Type; }

  eTextureWrapping GetWrapping() const { return m_Wrapping; }
  eTextureFiltering GetFiltering() const { return m_Filtering; }

  virtual void SetWrapping(eTextureWrapping wrapping) = 0;
  virtual void SetFiltering(eTextureFiltering filtering) = 0;

  const glm::ivec3 GetSize() const { return m_Size; }
  int GetWidth() const { return m_Size.x; }
  int GetHeight() const { return m_Size.y; }
  int GetDepth() const { return m_Size.z; }

protected:
  eTextureUsage m_Usage;
  eTextureType m_Type;
  ePixelFormat m_PixelFormat;
  eTextureWrapping m_Wrapping;
  eTextureFiltering m_Filtering;

  glm::ivec3 m_Size;

  iLowLevelGraphics& m_LowLevelGraphics;
};
} // namespace Lumeda