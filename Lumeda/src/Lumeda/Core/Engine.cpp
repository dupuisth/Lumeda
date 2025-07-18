#include <Lumeda/Core/Engine.h>

#include <iostream>

using namespace Lumeda;

Engine::Engine() { }

Engine::~Engine() { }

void Engine::TestPrint(const std::string& text)
{
	std::cout << "[ENGINE] " << text << std::endl;
}