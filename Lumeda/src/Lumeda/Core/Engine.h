#pragma once

#include <Lumeda/Core/Base.h>

#include <Lumeda/Core/Window.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Imgui/ImGuiLayer.h>

#include <string>

namespace Lumeda 
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		void Run(Layer& application);

		Window& GetWindow() { return *m_Window; }
		Renderer& GetRenderer() { return *m_Renderer; }

		static Engine& Get();
	private:
		Layer* m_Application;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
	};
}