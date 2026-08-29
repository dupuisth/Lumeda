#pragma once

#include <set>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{

class iResourceLoader : public iUpdateable
{
public:
  iResourceLoader(const tString& name) : iUpdateable(name) {}
  virtual ~iResourceLoader() = default;

  void AddSupportedExtensions(const tString& ext) { m_SupportedExtensions.insert(ext); }
  bool IsExtensionSupported(const tString& ext) { return m_SupportedExtensions.contains(ext); }

  virtual void PreLoad(const twString& path) = 0;
  virtual void LoadPending() = 0;

protected:
  std::set<tString> m_SupportedExtensions;
};

} // namespace Lumeda