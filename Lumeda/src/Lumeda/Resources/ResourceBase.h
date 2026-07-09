#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
class iResourceBase
{
public:
  iResourceBase(const tString& name, const twString& path);

  virtual ~iResourceBase();

  /**
   * Reload the asset
   */
  virtual bool Reload() = 0;

  /**
   * Free most of the memory, keep some infos for later reload
   */
  virtual void Unload() = 0;

  /**
   * Free all memory
   */
  virtual void Destroy() = 0;

  const tString& GetName() { return m_Name; }
  void SetName(const tString& name);

  const twString& GetPath() { return m_Path; }

  unsigned int GetUserCount() { return m_UserCount; }
  bool HasUsers() { return m_UserCount > 0; }
  void IncrementUserCount();
  void DecrementUserCount();

protected:
  void SetPath(const twString& path) { m_Path = path; }

private:
  tString m_Name;
  twString m_Path;

  unsigned int m_UserCount;
};
} // namespace Lumeda