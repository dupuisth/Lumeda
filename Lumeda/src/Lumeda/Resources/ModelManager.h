#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/Model.h>
#include <Lumeda/Resources/ResourceManager.h>

namespace Lumeda
{
class Graphics;

class ModelManager : public iResourceManager<Model>
{
public:
  ModelManager(Resources& resources, Graphics& graphics) : iResourceManager(resources), m_Graphics(graphics) {}
  ~ModelManager() = default;

  Model* CreateModel(const tString& name);
  Model* CreateModel(const tString& name, const twString& path);

private:
  Graphics& m_Graphics;
};
} // namespace Lumeda