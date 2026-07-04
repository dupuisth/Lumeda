#include <Lumeda/Graphics/GpuShader.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Resources/GpuShaderManager.h>

using namespace Lumeda;

iGpuShader* GpuShaderManager::CreateShader(const tString& name, const twString& path, eShaderType type)
{
  std::unique_ptr<iGpuShader> shader = m_Graphics.GetLowLevelGraphics().CreateShader(name, path, type);
  iGpuShader* rawPtr = AddResource(std::move(shader));
  return rawPtr;
}
