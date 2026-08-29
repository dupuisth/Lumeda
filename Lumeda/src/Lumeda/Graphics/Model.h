#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Graphics/VertexBuffer.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class Material;

class ModelItem
{
public:
  std::unique_ptr<iVertexBuffer> vertexBuffer;
  int materialIndex;
};

class Model : public iResourceBase
{
public:
  Model(const tString& name, const twString& path) : iResourceBase(name, path) {}

  ///////////////////////////////////////////
  // Lifetime
  ///////////////////////////////////////////
  bool Reload() { return false; }
  void Unload() {}
  void Destroy() {}

  void AddItem(std::unique_ptr<iVertexBuffer> vertexBuffer, int materialIndex) { m_Items.push_back({std::move(vertexBuffer), materialIndex}); }
  std::vector<ModelItem>& GetItems() { return m_Items; }
  std::vector<Material*>& GetMaterials() { return m_Materials; }

private:
  std::vector<ModelItem> m_Items;
  std::vector<Material*> m_Materials;
};

} // namespace Lumeda