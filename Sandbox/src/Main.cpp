#include <Lumeda/Lumeda.h>
#include <Sandbox/SandboxBase.h>

using namespace Sandbox;

std::unique_ptr<SandboxBase> sandboxBase = nullptr;

SandboxBase& Sandbox::GetSandboxBase()
{
  return *sandboxBase;
}

int lumedaMain()
{
  int status = EXIT_SUCCESS;
  {
    sandboxBase = std::make_unique<SandboxBase>();

    if (sandboxBase->Init())
    {
      sandboxBase->Run();
      sandboxBase->Exit();
    }
    else
    {
      // Something went wrong
      status = EXIT_FAILURE;
    }

    // Force delete before the end of the execution, or spdlog will make the program crash
    sandboxBase.reset();
  }

  return status;
}