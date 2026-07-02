#pragma once

#include <string>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Engine/EventReceiver.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Engine/Updater.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Imgui/ImGuiLayer.h>

namespace Lumeda
{

class Engine : public iEventReceiver, public iUpdateable
{
public:
  Engine(std::unique_ptr<iLowLevelEngineSetup> lowLevelEngineSetup);
  ~Engine();

  void Run();

  ///////////////////////////////////////////
  // Getters
  ///////////////////////////////////////////
  Graphics& GetGraphics() { return *m_Graphics; }
  Updater& GetUpdater() { return *m_Updater; }
  EventManager& GetEventManager() { return *m_EventManager; }
  //---------------------------------------//

  ///////////////////////////////////////////
  // Events
  ///////////////////////////////////////////
  bool OnEvent(iEvent& event) override;
  //---------------------------------------//

  ///////////////////////////////////////////
  // Static
  ///////////////////////////////////////////
  static std::unique_ptr<Engine> CreateLumedaEngine(eLumedaBackend backend);
  static Engine& Get();
  //---------------------------------------//

private:
  void Cleanup();

private:
  bool m_ShouldClose;

  ///////////////////////////////////////////
  // Layers
  ///////////////////////////////////////////
  std::unique_ptr<Graphics> m_Graphics;
  //---------------------------------------//

  std::unique_ptr<iLowLevelEngineSetup> m_LowLevelEngineSetup;

  std::unique_ptr<EventManager> m_EventManager;
  std::unique_ptr<Updater> m_Updater;
};
} // namespace Lumeda

#define LUMEDA_TIME (Lumeda::Engine::Get().GetTime())
#define LUMEDA_ENGINE (Lumeda::Engine::Get())