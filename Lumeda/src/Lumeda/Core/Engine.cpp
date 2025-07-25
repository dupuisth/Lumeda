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

	// Initialize the Renderer
	m_Renderer = Renderer::Create();
	if (m_Renderer == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create renderer");
		throw std::runtime_error("Failed to create renderer");
	}
	m_Renderer->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
	m_Renderer->SetClearColor(0.02f, 0.05f, 0.13f, 1.0f);
	LUMEDA_CORE_INFO("Renderer initialized");

	// Initialize ImGui
	m_ImGuiLayer = std::make_unique<ImGuiLayer>();
	m_ImGuiLayer->Initialize();
	LUMEDA_CORE_INFO("ImGui initialized");
}

Engine::~Engine() { }

void Engine::Run(std::unique_ptr<Layer> application)
{
	LUMEDA_PROFILE;
	m_Application = std::move(application);

	LUMEDA_CORE_INFO("Starting the game loop");
	
	m_Application->Initialize();
	while (!m_Window->ShouldClose())
	{
		LUMEDA_PROFILE_FRAME;

		m_Renderer->Clear();

		m_Application->Update();
		m_Application->Render();

		m_ImGuiLayer->Begin();
		m_Application->RenderImGui();
		m_ImGuiLayer->End();

		m_Window->Update();
	}
	m_Application->Terminate();

	// Destroy Application
	m_Application->Terminate();
	m_Application.reset();

	// Destroy ImGui
	m_ImGuiLayer->Terminate();
	m_ImGuiLayer.reset();

	// Destroy the renderer
	m_Renderer.reset();

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

Engine& Engine::Get()
{
	LUMEDA_PROFILE;
	return *s_Instance;
}
