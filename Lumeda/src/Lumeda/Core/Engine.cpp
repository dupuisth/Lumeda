#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Log.h>

#include <iostream>

using namespace Lumeda;

Engine::Engine() : m_Application(nullptr) 
{
	// Initialize the engine
	Log::Init();
	LUMEDA_CORE_TRACE("Logger initialized");

	m_Window = Window::Create();
	if (m_Window == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create window");
		throw std::runtime_error("Failed to create window");
	}
	LUMEDA_CORE_INFO("Window initialized");

	m_Renderer = Renderer::Create();
	if (m_Renderer == nullptr)
	{
		LUMEDA_CORE_CRITICAL("Failed to create renderer");
		throw std::runtime_error("Failed to create renderer");
	}
	m_Renderer->SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
	m_Renderer->SetClearColor(0.02f, 0.05f, 0.13f, 1.0f);
	LUMEDA_CORE_INFO("Renderer initialized");
}

Engine::~Engine() { }

void Engine::Run(IApplication& application)
{
	m_Application = &application;

	LUMEDA_CORE_INFO("Starting the game loop");
	
	m_Application->Initialize();
	while (!m_Window->ShouldClose())
	{
		m_Renderer->Clear();

		m_Application->Update();
		m_Application->Render();
		
		m_Window->Update();
	}
	m_Application->Terminate();

	// Destroy the renderer
	m_Renderer.reset();

	// Destroy the window
	m_Window.reset();


	LUMEDA_CORE_INFO("Game loop ended");
}
