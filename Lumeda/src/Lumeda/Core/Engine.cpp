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
	LUMEDA_CORE_INFO("Window initialized");
}

Engine::~Engine() { }

void Engine::Run(IApplication& application)
{
	m_Application = &application;

	LUMEDA_CORE_INFO("Starting the game loop");
	
	m_Application->Initialize();
	for (int i = 0; i < 2; i++) // For now, just run 2 frames to test
	{
		m_Window->Update();

		m_Application->Update();
		m_Application->Render();
	}
	m_Application->Terminate();

	// Destroy the window
	m_Window.reset();

	LUMEDA_CORE_INFO("Game loop ended");
}
