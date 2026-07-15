#include <Lumeda/Resources/ModelManager.h>
#include <Lumeda/Utils/AssimpModelLoader.h>

using namespace Lumeda;

Model* ModelManager::CreateModel(const tString& name)
{
  std::unique_ptr<Model> model = std::make_unique<Model>(name, _W(""));
  return AddResource(std::move(model));
}

Model* Lumeda::ModelManager::CreateModel(const tString& name, const twString& path)
{
  std::unique_ptr<Model> model = std::make_unique<Model>(name, path);
  AssimpModelLoader::Load(model.get(), path, m_Graphics, m_Resources);
  return AddResource(std::move(model));
}