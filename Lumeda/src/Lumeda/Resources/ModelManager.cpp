#include <Lumeda/Resources/ModelManager.h>

using namespace Lumeda;

Model* ModelManager::CreateModel(const tString& name)
{
  std::unique_ptr<Model> model = std::make_unique<Model>(name, _W(""));
  return AddResource(std::move(model));
}

Model* Lumeda::ModelManager::CreateModel(const tString& name, const twString& path)
{
  std::unique_ptr<Model> model = std::make_unique<Model>(name, path);
}