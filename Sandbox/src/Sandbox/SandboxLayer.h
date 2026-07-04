#pragma once

#include <Lumeda/Lumeda.h>

namespace Sandbox
{
class SandboxLayer : public Lumeda::iUpdateable
{
public:
  SandboxLayer() : Lumeda::iUpdateable("SandboxLayer") {}
  ~SandboxLayer() = default;

  void OnStart() override;
  void OnDraw() override;
};

} // namespace Sandbox
