#include <Lumeda/Imgui/ImGuiLayer.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Window.h>

#include <glad/glad.h>

#include <imgui.h>

#ifdef LUMEDA_USE_GLAD
#include <imgui_impl_opengl3.h>
#else
#error Current platform not supported! 
#endif

#ifdef LUMEDA_USE_GLFW
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



#if defined(LUMEDA_USE_GLFW) && defined(LUMEDA_USE_GLAD)
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Engine::Get().GetWindow().GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
#else
#error Current platform not supported! 
#endif
}

void ImGuiLayer::Terminate()
{
	LUMEDA_PROFILE;
#if defined(LUMEDA_USE_GLFW) && defined(LUMEDA_USE_GLAD)
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
#if defined(LUMEDA_USE_GLFW) && defined(LUMEDA_USE_GLAD)
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
#if defined(LUMEDA_USE_GLFW) && defined(LUMEDA_USE_GLAD)
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#else
#error Current platform not supported! 
#endif
}
