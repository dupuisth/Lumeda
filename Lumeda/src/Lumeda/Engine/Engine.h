#pragma once

#include <string>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventQueue.h>
#include <Lumeda/Engine/EventReceiver.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Imgui/ImGuiLayer.h>

namespace Lumeda
{

class Engine
{
public:
  Engine(std::unique_ptr<iLowLevelEngineSetup> lowLevelEngineSetup);
  ~Engine();

  void Run();

  Graphics& GetGraphics() { return *m_Graphics; }

  ///////////////////////////////////////////
  // Static
  ///////////////////////////////////////////
  static std::unique_ptr<Engine> CreateLumedaEngine(eLumedaBackend backend);
  static Engine& Get();

private:
  void PollEvents();
  void HandleEvent(iEvent& event);
  void Broadcast(eUpdateableMessage message);

  void Cleanup();

private:
  bool m_ShouldClose;

  ///////////////////////////////////////////
  // Layers
  ///////////////////////////////////////////
  std::unique_ptr<Graphics> m_Graphics;
  //---------------------------------------//

  std::unique_ptr<iLowLevelEngineSetup> m_LowLevelEngineSetup;

  std::unique_ptr<EventQueue> m_EventQueue;

  ///////////////////////////////////////////
  // Lists for simplier iterations
  ///////////////////////////////////////////
  std::vector<iEventReceiver*> m_EventReceivers;
  std::vector<iUpdateable*> m_Updateables;
  //---------------------------------------//
};
} // namespace Lumeda

#define LUMEDA_TIME (Lumeda::Engine::Get().GetTime())
#define LUMEDA_ENGINE (Lumeda::Engine::Get())