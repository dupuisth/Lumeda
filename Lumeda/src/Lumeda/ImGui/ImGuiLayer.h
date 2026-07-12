#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
class iImGuiLayer : public iUpdateable
{
public:
  iImGuiLayer() : iUpdateable("ImGuiLayer") {}
  virtual ~iImGuiLayer() = default;

  virtual void OnStart() = 0;

  virtual void OnPreDraw() = 0;
  virtual void OnPostDraw() = 0;
};
} // namespace Lumeda