#include <Lumeda/Core/Log.h>
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Implementation/GL/LowLevelEngineSetupGL.h>

using namespace Lumeda;

Engine* s_Instance = nullptr;

Engine::Engine(std::unique_ptr<iLowLevelEngineSetup> lowLevelEngineSetup) :
    iUpdateable("Engine"), m_LowLevelEngineSetup(std::move(lowLevelEngineSetup)), m_ShouldClose(false), m_EventManager(nullptr), m_Updater(nullptr)
{
  LUMEDA_PROFILE;

  s_Instance = this;
  m_Updater = std::make_unique<Updater>();

  ///////////////////////////////////////////
  // Create dependencies
  ///////////////////////////////////////////
  m_Resources = std::make_unique<Resources>();

  m_Graphics = m_LowLevelEngineSetup->GetGraphics();
  m_Graphics->GetLowLevelGraphics().Init(800, 600, "Lumeda Engine");
  m_Resources->Init(*m_Graphics);

  // Last
  m_EventManager = m_LowLevelEngineSetup->GetEventManager();
  //---------------------------------------//

  ///////////////////////////////////////////
  // Register default updateable
  ///////////////////////////////////////////
  m_Updater->AddUpdateable(this);
  m_Updater->AddUpdateable(m_Resources.get());
  m_Updater->AddUpdateable(m_Graphics.get());
  //---------------------------------------//

  m_EventManager->AddReceiver(this);
  m_EventManager->AddReceiver(m_Graphics.get());
}

Engine::~Engine()
{
  LUMEDA_PROFILE;

  Cleanup();
}

void Engine::Run()
{
  LUMEDA_CORE_INFO("[Engine] Starting the game loop");

  m_Updater->BroadcastMessage(eUpdateableMessage_OnStart);
  while (!m_ShouldClose)
  {
    LUMEDA_PROFILE_FRAME;

    ///////////////////////////////////////////
    // Update
    ///////////////////////////////////////////
    m_Updater->BroadcastMessage(eUpdateableMessage_PreUpdate);
    m_Updater->BroadcastMessage(eUpdateableMessage_Update);
    m_Updater->BroadcastMessage(eUpdateableMessage_PostUpdate);

    ///////////////////////////////////////////
    // Drawing
    ///////////////////////////////////////////
    m_Updater->BroadcastMessage(eUpdateableMessage_OnPreDraw);
    m_Graphics->GetLowLevelGraphics().ClearFrameBuffer(tClearFrameBufferFlag_Color);
    m_Updater->BroadcastMessage(eUpdateableMessage_OnDraw);
    m_Updater->BroadcastMessage(eUpdateableMessage_OnPostDraw);
    m_Graphics->GetLowLevelGraphics().SwapBuffers();

    ///////////////////////////////////////////
    // Event handling
    ///////////////////////////////////////////
    m_EventManager->PollEvents();
  }
  LUMEDA_CORE_INFO("[Engine] Game loop ended");
}

bool Engine::OnEvent(iEvent& event)
{
  // Handle basics events
  if (event.GetType() == eGraphicsEvent_WindowShouldClose)
  {
    m_ShouldClose = true;
    return true;
  }

  return false;
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