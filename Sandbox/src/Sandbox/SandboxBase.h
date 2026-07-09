#pragma once

#include <Lumeda/Lumeda.h>
#include <Sandbox/SandboxLayer.h>

namespace Sandbox
{
class SandboxBase
{
public:
  SandboxBase();
  ~SandboxBase();

  bool Init();
  void Exit();

  void Run();

  void Reset();

  Lumeda::Engine& GetEngine() { return *m_Engine; }

private:
  std::unique_ptr<Lumeda::Engine> m_Engine;

  std::unique_ptr<SandboxLayer> m_SandboxLayer;
};

extern SandboxBase& GetSandboxBase();

} // namespace Sandbox
