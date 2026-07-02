#pragma once

#include <Lumeda/Lumeda.h>

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

    Lumeda::Engine& GetEngine() { return *m_engine; }

  private:
    std::unique_ptr<Lumeda::Engine> m_engine;
};

extern SandboxBase& GetSandboxBase();

} // namespace Sandbox
