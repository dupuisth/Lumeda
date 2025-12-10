#pragma once

#include <Lumeda/Core/Base.h>

#include <Lumeda/Core/Window.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Imgui/ImGuiLayer.h>
#include <Lumeda/Core/InputsLayer.h>

#include <string>

namespace Lumeda 
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		void Run(std::unique_ptr<Layer> application);

		Window& GetWindow();
		Renderer& GetRenderer();

		static Engine& Get();
	private:
		std::unique_ptr<Layer> m_Application;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		std::unique_ptr<InputsLayer> m_InputsLayer;
	};
}