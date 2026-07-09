#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Resources/ResourceManager.h>

namespace Lumeda
{
class iGpuShader;
class Graphics;

class GpuShaderManager : public iResourceManager<iGpuShader>
{
public:
  GpuShaderManager(Resources& resources, Graphics& graphics) : iResourceManager(resources), m_Graphics(graphics) {}
  ~GpuShaderManager() = default;

  iGpuShader* CreateShader(const tString& name, const twString& path, eShaderType type);

private:
  Graphics& m_Graphics;
};
} // namespace Lumeda