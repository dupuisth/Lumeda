#include <Lumeda/Imgui/ImGuiLayer.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Window.h>

#include <glad/glad.h>

#include <imgui.h>

#if LUMEDA_PLATFORM_WINDOWS
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#else
#error Only windows is supported
#endif

using namespace Lumeda;

ImGuiLayer::ImGuiLayer()
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::Initialize()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#endif
}

void ImGuiLayer::Terminate()
{
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
#endif

	ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
}

void ImGuiLayer::End()
{
	ImGui::Render();
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}
