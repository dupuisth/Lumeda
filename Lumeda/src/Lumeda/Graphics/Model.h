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
  Material* material;
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

  void AddItem(std::unique_ptr<iVertexBuffer> vertexBuffer, Material* material) { m_Items.push_back({std::move(vertexBuffer), material}); }
  const std::vector<ModelItem>& GetItems() { return m_Items; }

private:
  std::vector<ModelItem> m_Items;
};

} // namespace Lumeda