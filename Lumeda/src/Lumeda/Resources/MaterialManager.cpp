#include <Lumeda/Resources/MaterialManager.h>

using namespace Lumeda;

Material* MaterialManager::CreateMaterial(const tString& name)
{
  std::unique_ptr<Material> material = std::make_unique<Material>(name, _W(""));
  return AddResource(std::move(material));
}

Material* Lumeda::MaterialManager::CreateMaterial(const tString& name, const twString& path)
{
  std::unique_ptr<Material> material = std::make_unique<Material>(name, path);

  return AddResource(std::move(material));
}