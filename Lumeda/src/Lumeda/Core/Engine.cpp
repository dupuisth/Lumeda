#include <Lumeda/Core/Engine.h>

#include <iostream>

using namespace Lumeda;

Engine::Engine() { }

Engine::~Engine() { }

void Engine::Run(IApplication& application)
{
	m_Application = &application;

	m_Application->Initialize();
	while (true)
	{
		m_Application->Update();
		m_Application->Render();
	}
	m_Application->Terminate();
}
