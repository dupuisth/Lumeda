#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Resources/ResourceManager.h>

namespace Lumeda
{
class Graphics;

class MaterialManager : public iResourceManager<Material>
{
public:
  MaterialManager(Resources& resources, Graphics& graphics) : iResourceManager(resources), m_Graphics(graphics) {}
  ~MaterialManager() = default;

  Material* CreateMaterial(const tString& name);
  Material* CreateMaterial(const tString& name, const twString& path);

private:
  Graphics& m_Graphics;
};
} // namespace Lumeda