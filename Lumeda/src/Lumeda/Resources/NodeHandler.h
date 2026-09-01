#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class iNodeHandler : public iUpdateable
{
public:
  iNodeHandler(const tString& name) : iUpdateable(name) {}
  virtual ~iNodeHandler() = default;

  virtual tString GetHandlerTypeId() const = 0;
};
} // namespace Lumeda