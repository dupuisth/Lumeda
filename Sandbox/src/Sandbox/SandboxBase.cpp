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
  m_Engine = Engine::CreateLumedaEngine(eLumedaBackend_OpenGL);

  m_SandboxLayer = std::make_unique<SandboxLayer>();
  m_Engine->GetUpdater().AddUpdateable(m_SandboxLayer.get());

  return true;
}

void Sandbox::SandboxBase::Exit()
{
}

void SandboxBase::Run()
{
  m_Engine->Run();
}

void SandboxBase::Reset()
{
}