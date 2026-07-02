#include <Sandbox/SandboxBase.h>

using namespace Sandbox;
using namespace Lumeda;

SandboxBase::SandboxBase()
{
}

SandboxBase::~SandboxBase()
{
}

bool SandboxBase::Init()
{
  Log::Init();
  m_engine = Engine::CreateLumedaEngine(eLumedaBackend_OpenGL);

  return true;
}

void Sandbox::SandboxBase::Exit()
{
}

void SandboxBase::Run()
{
  m_engine->Run();
}

void SandboxBase::Reset()
{
}