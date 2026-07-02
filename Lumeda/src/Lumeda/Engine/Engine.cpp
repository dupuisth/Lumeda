#include <Lumeda/Core/Log.h>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>

using namespace Lumeda;

Engine* s_Instance = nullptr;

Engine::Engine(std::unique_ptr<iLowLevelEngineSetup> lowLevelEngineSetup) : m_LowLevelEngineSetup(std::move(lowLevelEngineSetup))
{
  LUMEDA_PROFILE;

  s_Instance = this;

  m_Graphics = m_LowLevelEngineSetup->GetGraphics();

  m_Graphics->GetLowLevelGraphics().Init(800, 600, "Lumeda Engine");
}

Engine::~Engine()
{
  LUMEDA_PROFILE;

  Cleanup();
}

void Engine::Run()
{
  LUMEDA_CORE_INFO("[Engine] Starting the game loop");

  while (true)
  {
    LUMEDA_PROFILE_FRAME;

    m_Graphics->GetLowLevelGraphics().ClearFrameBuffer(tClearFrameBufferFlag_Color);
    m_Graphics->GetLowLevelGraphics().SwapBuffers();
  }
  LUMEDA_CORE_INFO("[Engine] Game loop ended");
}

void Engine::Cleanup()
{
  LUMEDA_CORE_INFO("[Engine] Cleaning up engine");
}

Engine& Engine::Get()
{
  return *s_Instance;
}

std::unique_ptr<Engine> Engine::CreateLumedaEngine(eLumedaBackend backend)
{
  std::unique_ptr<iLowLevelEngineSetup> engineSetup = nullptr;

  switch (backend)
  {
  case eLumedaBackend_OpenGL:
    engineSetup = std::make_unique<LowLevelEngineSetupGL>();
    break;
  }

  return std::make_unique<Engine>(std::move(engineSetup));
}