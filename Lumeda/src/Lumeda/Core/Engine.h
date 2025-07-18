#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/IApplication.h>
#include <Lumeda/Core/Window.h>

#include <string>

namespace Lumeda 
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		void Run(IApplication& application);

		Window& GetWindow() { return *m_Window; }

	private:
		IApplication* m_Application;

		std::unique_ptr<Window> m_Window;
	};
}