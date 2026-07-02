#include <Lumeda/Resources/ResourceBase.h>

using namespace Lumeda;

iResourceBase::iResourceBase(const tString& name, const twString& path) : m_Name(name), m_Path(path)
{
  m_UserCount = 0;
}

iResourceBase::~iResourceBase()
{
}

void iResourceBase::SetName(const tString& name)
{
  m_Name = name;
}

void iResourceBase::IncrementUserCount()
{
  m_UserCount++;
}

void iResourceBase::DecrementUserCount()
{
  if (m_UserCount > 0)
    m_UserCount--;
}