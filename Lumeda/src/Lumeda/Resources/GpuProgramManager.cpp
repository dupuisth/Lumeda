#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Resources/GpuProgramManager.h>

using namespace Lumeda;

iGpuProgram* GpuProgramManager::CreateProgram(const tString& name)
{
  std::unique_ptr<iGpuProgram> program = m_Graphics.GetLowLevelGraphics().CreateProgram(name);
  iGpuProgram* rawPtr = AddResource(std::move(program));
  return rawPtr;
}
