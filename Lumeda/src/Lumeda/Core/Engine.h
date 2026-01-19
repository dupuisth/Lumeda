#pragma once

#include <Lumeda/Core/Base.h>

#include <Lumeda/Core/Window.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Imgui/ImGuiLayer.h>
#include <Lumeda/Core/InputsLayer.h>
#include <Lumeda/Gizmos/Gizmos.h>
#include <Lumeda/Core/Time.h>

#include <string>

namespace Lumeda
{
	class Framebuffer;
	class Texture2D;

	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run(Layer* application);

		Window& GetWindow();
		Renderer& GetRenderer();
		Gizmos& GetGizmos();
		Time& GetTime();

		static Engine& Get();

	private:
		void Cleanup();

	private:
		Layer* m_Application;

		Window* m_Window;
		Renderer* m_Renderer;
		ImGuiLayer* m_ImGuiLayer;
		InputsLayer* m_InputsLayer;
		Gizmos* m_Gizmos;
		Time* m_Time;
	};
}