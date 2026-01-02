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
	LUMEDA_CORE_TRACE("Logger initialized");

	// Initialize the Window
	m_Window = Window::Create();
	if (m_Window == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create window");
		throw std::runtime_error("Failed to create window");
	}
	LUMEDA_CORE_INFO("Window initialized");

	// Initialize the input layer
	m_InputsLayer = InputsLayer::Create();
	if (m_InputsLayer == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create inputs layer");
		throw std::runtime_error("Failed to create inputs layer");
	}
	LUMEDA_CORE_INFO("Inputs layer initialized");

	// Initialize the Renderer
	m_Renderer = Renderer::Create();
	if (m_Renderer == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create renderer");
		throw std::runtime_error("Failed to create renderer");
	}
	m_Renderer->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
	m_Renderer->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	LUMEDA_CORE_INFO("Renderer initialized");

	// Initialize ImGui
	m_ImGuiLayer = std::make_unique<ImGuiLayer>();
	m_ImGuiLayer->Initialize();
	LUMEDA_CORE_INFO("ImGui initialized");

	m_Gizmos = Gizmos::Create();
	m_Gizmos->Initialize();
	LUMEDA_CORE_INFO("Gizmos initialized");
}

Engine::~Engine() {}

void Engine::Run(std::unique_ptr<Layer> application)
{
	LUMEDA_PROFILE;
	m_Application = std::move(application);

	LUMEDA_CORE_INFO("Starting the game loop");

	m_Application->Initialize();
	while (!m_Window->ShouldClose())
	{
		LUMEDA_PROFILE_FRAME;
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

	// Destroy Application
	m_Application->Terminate();
	m_Application.reset();

	// Destroy Gizmos
	m_Gizmos->Terminate();
	m_Gizmos.reset();

	// Destroy ImGui
	m_ImGuiLayer->Terminate();
	m_ImGuiLayer.reset();

	// Destroy the renderer
	m_Renderer.reset();

	// Destroy the inputs layer
	m_InputsLayer.reset();

	// Destroy the window
	m_Window.reset();

	LUMEDA_CORE_INFO("Game loop ended");
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

Engine& Engine::Get()
{
	LUMEDA_PROFILE;
	return *s_Instance;
}
