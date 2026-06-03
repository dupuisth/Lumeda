#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/InputsLayer.h>
#include <Lumeda/Core/Time.h>
#include <Lumeda/Core/Window.h>
#include <Lumeda/Gizmos/Gizmos.h>
#include <Lumeda/Imgui/ImGuiLayer.h>
#include <Lumeda/Renderer/Renderer.h>
#include <string>

namespace Lumeda
{
class Framebuffer;
class Texture2D;

class Engine
{
  public:
    Engine();
    ~Engine();

    void Run(Layer* application);

    Window& GetWindow();
    Renderer& GetRenderer();
    Gizmos& GetGizmos();
    Time& GetTime();

    static Engine& Get();

  private:
    void Cleanup();

  private:
    Layer* m_Application;

    Window* m_Window;
    Renderer* m_Renderer;
    ImGuiLayer* m_ImGuiLayer;
    InputsLayer* m_InputsLayer;
    Gizmos* m_Gizmos;
    Time* m_Time;
};
} // namespace Lumeda

#define LUMEDA_RENDERER (Lumeda::Engine::Get().GetRenderer())
#define LUMEDA_TIME (Lumeda::Engine::Get().GetTime())
#define LUMEDA_GIZMOS (Lumeda::Engine::Get().GetGizmos())
#define LUMEDA_WINDOW (Lumeda::Engine::Get().GetWindow())
#define LUMEDA_ENGINE (Lumeda::Engine::Get())