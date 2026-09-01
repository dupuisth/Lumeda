#pragma once

#include <string>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Engine/EventReceiver.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>
#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Engine/Updater.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/ImGui/ImGuiLayer.h>
#include <Lumeda/Inputs/Inputs.h>
#include <Lumeda/Resources/Resources.h>

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
  Resources& GetResources() { return *m_Resources; }
  Updater& GetUpdater() { return *m_Updater; }
  EventManager& GetEventManager() { return *m_EventManager; }
  iImGuiLayer& GetImGui() { return *m_ImGui; }
  iInputs& GetInputs() { return *m_Inputs; }
  Timer& GetTimer() { return *m_Timer; }
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

  std::unique_ptr<EventManager> m_EventManager;
  std::unique_ptr<Updater> m_Updater;

  std::unique_ptr<iLowLevelEngineSetup> m_LowLevelEngineSetup;

  ///////////////////////////////////////////
  // Layers (respect the order)
  ///////////////////////////////////////////
  std::unique_ptr<Graphics> m_Graphics;
  std::unique_ptr<Resources> m_Resources;
  std::unique_ptr<iImGuiLayer> m_ImGui;
  std::unique_ptr<Timer> m_Timer;
  std::unique_ptr<iInputs> m_Inputs;
  //---------------------------------------//
};
} // namespace Lumeda