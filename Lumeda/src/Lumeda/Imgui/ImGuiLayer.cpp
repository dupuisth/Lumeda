#include <Lumeda/Imgui/ImGuiLayer.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Window.h>

#include <glad/glad.h>

#include <imgui.h>

#if LUMEDA_PLATFORM_WINDOWS
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#elif LUMEDA_PLATFORM_LINUX
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#else
#error Current platform not supported! 
#endif

using namespace Lumeda;

ImGuiLayer::ImGuiLayer()
{
	LUMEDA_PROFILE;
}

ImGuiLayer::~ImGuiLayer()
{
	LUMEDA_PROFILE;
}

void ImGuiLayer::Initialize()
{
	LUMEDA_PROFILE;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#elif LUMEDA_PLATFORM_LINUX
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#else
#error Current platform not supported! 
#endif
}

void ImGuiLayer::Terminate()
{
	LUMEDA_PROFILE;
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
#elif LUMEDA_PLATFORM_LINUX
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
#else
#error Current platform not supported! 
#endif

	ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
	LUMEDA_PROFILE;
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#elif LUMEDA_PLATFORM_LINUX
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#else
#error Current platform not supported! 
#endif
}

void ImGuiLayer::End()
{
	LUMEDA_PROFILE;
	ImGui::Render();
#if LUMEDA_PLATFORM_WINDOWS
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#elif LUMEDA_PLATFORM_LINUX
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#else
#error Current platform not supported! 
#endif
}
