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
  m_engine->GetGraphics().GetLowLevelGraphics().SetClearColor({0.001f, 0.07f, 0.14f, 1.0f});
  m_engine->Run();
}

void SandboxBase::Reset()
{
}