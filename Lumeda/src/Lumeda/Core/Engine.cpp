#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Log.h>

using namespace Lumeda;

Engine* s_Instance = nullptr;

Engine::Engine() : m_Application()
{
    LUMEDA_PROFILE;

    s_Instance = this;

    // Initialize the Logger
    Log::Init();
    LUMEDA_CORE_TRACE("[Engine] Logger initialized");

    // Initialize the Window
    m_Window = Window::Create();
    if (m_Window == nullptr)
    {
        LUMEDA_CORE_CRITICAL("[Engine] Failed to create window");
        throw std::runtime_error("Failed to create window");
    }
    LUMEDA_CORE_INFO("[Engine] Window initialized");

    // Initialize the Time layer
    m_Time = Time::Create();
    if (m_Time == nullptr)
    {
        LUMEDA_CORE_CRITICAL("[Engine] Failed to create time layer");
        throw std::runtime_error("Failed to create time layer");
    }
    LUMEDA_CORE_INFO("[ENGINE] Time initialized");

    // Initialize the input layer
    m_InputsLayer = InputsLayer::Create();
    if (m_InputsLayer == nullptr)
    {
        LUMEDA_CORE_CRITICAL("[Engine] Failed to create inputs layer");
        throw std::runtime_error("Failed to create inputs layer");
    }
    LUMEDA_CORE_INFO("[Engine] Inputs layer initialized");

    // Initialize the Renderer
    m_Renderer = Renderer::Create();
    if (m_Renderer == nullptr)
    {
        LUMEDA_CORE_CRITICAL("[Engine] Failed to create renderer");
        throw std::runtime_error("Failed to create renderer");
    }
    m_Renderer->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
    m_Renderer->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    LUMEDA_CORE_INFO("[Engine] Renderer initialized");

    // Initialize ImGui
    m_ImGuiLayer = LUMEDA_NEW(ImGuiLayer);
    m_ImGuiLayer->Initialize();
    LUMEDA_CORE_INFO("[Engine] ImGui initialized");

    m_Gizmos = Gizmos::Create();
    m_Gizmos->Initialize();
    LUMEDA_CORE_INFO("[Engine] Gizmos initialized");
}

Engine::~Engine()
{
    LUMEDA_PROFILE;
    Cleanup();
}

void Engine::Run(Layer* application)
{
    m_Application = application;

    LUMEDA_CORE_INFO("[Engine] Starting the game loop");

    m_Application->Initialize();
    while (!m_Window->ShouldClose())
    {
        LUMEDA_PROFILE_FRAME;

        m_Time->Tick();

        {
            LUMEDA_PROFILE_SECTION("Update");
            m_InputsLayer->Update();
            m_Application->Update();
        }

        {
            LUMEDA_PROFILE_SECTION("Rendering");
            m_Renderer->Clear();
            m_Application->Render();
        }

        {
            LUMEDA_PROFILE_SECTION("ImGui Rendering");
            m_ImGuiLayer->Begin();
            m_Application->RenderImGui();
            m_ImGuiLayer->End();
        }

        {
            LUMEDA_PROFILE_SECTION("Window Update");
            m_Window->Update();
        }
    }
    LUMEDA_CORE_INFO("[Engine] Game loop ended");
}

void Engine::Cleanup()
{
    LUMEDA_CORE_INFO("[Engine] Cleaning up engine");

    // Destroy Application
    if (m_Application != nullptr)
    {
        m_Application->Terminate();
        LUMEDA_FREE(m_Application);
    }

    // Destroy Gizmos
    if (m_Gizmos != nullptr)
    {
        m_Gizmos->Terminate();
        LUMEDA_FREE(m_Gizmos);
    }

    // Destroy ImGui
    if (m_ImGuiLayer != nullptr)
    {
        m_ImGuiLayer->Terminate();
        LUMEDA_FREE(m_ImGuiLayer);
    }

    // Destroy the renderer
    if (m_Renderer != nullptr)
    {
        LUMEDA_FREE(m_Renderer);
    }

    // Destroy the inputs layer
    if (m_InputsLayer != nullptr)
    {
        LUMEDA_FREE(m_InputsLayer);
    }

    // Destroy the time layer
    if (m_Time != nullptr)
    {
        LUMEDA_FREE(m_Time);
    }

    // Destroy the window
    if (m_Window != nullptr)
    {
        LUMEDA_FREE(m_Window);
    }
}

Window& Engine::GetWindow()
{
    LUMEDA_PROFILE;
    return *m_Window;
}

Renderer& Engine::GetRenderer()
{
    LUMEDA_PROFILE;
    return *m_Renderer;
}

Gizmos& Engine::GetGizmos()
{
    LUMEDA_PROFILE;
    return *m_Gizmos;
}

Time& Engine::GetTime()
{
    LUMEDA_PROFILE;
    return *m_Time;
}

Engine& Engine::Get()
{
    LUMEDA_PROFILE;
    return *s_Instance;
}
