#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/TextureManager.h>

using namespace Lumeda;

iTexture* TextureManager::CreateTexture(const tString& name, eTextureType textureType, eTextureUsage usage)
{
  std::unique_ptr<iTexture> texture = m_Graphics.GetLowLevelGraphics().CreateTexture(name, textureType, usage);
  iTexture* rawPtr = AddResource(std::move(texture));
  return rawPtr;
}