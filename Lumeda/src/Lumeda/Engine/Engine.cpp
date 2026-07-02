#include <Lumeda/Core/Log.h>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>

using namespace Lumeda;

Engine* s_Instance = nullptr;

Engine::Engine(std::unique_ptr<iLowLevelEngineSetup> lowLevelEngineSetup) :
    m_LowLevelEngineSetup(std::move(lowLevelEngineSetup)), m_EventReceivers(), m_Updateables(), m_ShouldClose(false)
{
  LUMEDA_PROFILE;

  s_Instance = this;

  m_Graphics = m_LowLevelEngineSetup->GetGraphics();
  m_Updateables.push_back(m_Graphics.get());
  m_Graphics->GetLowLevelGraphics().Init(800, 600, "Lumeda Engine");

  // Last
  m_EventQueue = m_LowLevelEngineSetup->GetEventQueue();
}

Engine::~Engine()
{
  LUMEDA_PROFILE;

  Cleanup();
}

void Engine::Run()
{
  LUMEDA_CORE_INFO("[Engine] Starting the game loop");

  Broadcast(eUpdateableMessage_OnStart);
  while (!m_ShouldClose)
  {
    LUMEDA_PROFILE_FRAME;

    Broadcast(eUpdateableMessage_PreUpdate);
    Broadcast(eUpdateableMessage_Update);
    Broadcast(eUpdateableMessage_PostUpdate);

    Broadcast(eUpdateableMessage_OnPreDraw);
    m_Graphics->GetLowLevelGraphics().ClearFrameBuffer(tClearFrameBufferFlag_Color);
    Broadcast(eUpdateableMessage_OnDraw);
    Broadcast(eUpdateableMessage_OnPostDraw);
    m_Graphics->GetLowLevelGraphics().SwapBuffers();

    PollEvents();
  }
  LUMEDA_CORE_INFO("[Engine] Game loop ended");
}

void Engine::PollEvents()
{
  while (!m_EventQueue->IsEmpty())
  {
    std::unique_ptr<iEvent> event = m_EventQueue->PopEvent();
    HandleEvent(*event);
  }
}

void Engine::HandleEvent(iEvent& event)
{
  LUMEDA_CORE_TRACE("Handling event: {0}", event.GetType());

  // Handle basics events
  if (event.GetType() == eGraphicsEvent_WindowShouldClose)
  {
    m_ShouldClose = true;
    event.Handled = true;
    return;
  }

  // Else dispatch it
  for (const auto& eventReceiver : m_EventReceivers)
  {
    if (eventReceiver->OnEvent(event))
    {
      event.Handled = true;
      break;
    }
  }
}

void Engine::Broadcast(eUpdateableMessage message)
{
  for (const auto& updateable : m_Updateables)
  {
    updateable->HandleMessage(message);
  }
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