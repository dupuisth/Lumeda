#pragma once

#include <unordered_map>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceBase.h>

namespace Lumeda
{
class Resources;

template <typename T>
class iResourceManager
{
public:
  iResourceManager(Resources& resources) : m_Resources(resources) {}
  virtual ~iResourceManager() = default;

  T* GetResourceByName(const tString& name);
  const std::unordered_map<tString, std::unique_ptr<T>>& GetResources() { return m_Items; }

  T* AddResource(std::unique_ptr<T> resource);
  void DestroyResource(const tString& name);
  std::unique_ptr<T> RemoveResource(const tString& name);

protected:
  Resources& m_Resources;
  std::unordered_map<tString, std::unique_ptr<T>> m_Items;
};

template <typename T>
T* iResourceManager<T>::GetResourceByName(const tString& name)
{
  auto it = m_Items.find(name);
  if (it == m_Items.end())
    return nullptr;

  return it->second.get();
}

template <typename T>
T* iResourceManager<T>::AddResource(std::unique_ptr<T> resource)
{
  if (!resource)
  {
    return nullptr;
  }

  iResourceBase* resourceBase = static_cast<iResourceBase*>(resource.get());
  const tString& name = resourceBase->GetName();

  T* rawPtr = resource.get();
  m_Items.insert_or_assign(name, std::move(resource));

  return rawPtr;
}

template <typename T>
void iResourceManager<T>::DestroyResource(const tString& name)
{
  m_Items.erase(name);
}

template <typename T>
std::unique_ptr<T> iResourceManager<T>::RemoveResource(const tString& name)
{
  auto it = m_Items.find(name);
  if (it == m_Items.end())
    return nullptr;

  std::unique_ptr<T> item = std::move(it->second);
  m_Items.erase(it);

  return item;
}
} // namespace Lumeda
