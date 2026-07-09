#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceManager.h>

namespace Lumeda
{
class iGpuProgram;
class Graphics;

class GpuProgramManager : public iResourceManager<iGpuProgram>
{
public:
  GpuProgramManager(Resources& resources, Graphics& graphics) : iResourceManager(resources), m_Graphics(graphics) {}
  ~GpuProgramManager() = default;

  iGpuProgram* CreateProgram(const tString& name);

private:
  Graphics& m_Graphics;
};
} // namespace Lumeda