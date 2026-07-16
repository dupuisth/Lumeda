#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Implementation/GL/ImGuiLayerGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>

using namespace Lumeda;

ImGuiLayerGL::~ImGuiLayerGL()
{
  if (m_IsInitialized)
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }
}

void ImGuiLayerGL::OnStart()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  ImGui::StyleColorsLight();

  ImGui_ImplGlfw_InitForOpenGL(m_LowLevelGraphics.GetOpenGLWindow(), true);
  ImGui_ImplOpenGL3_Init(m_LowLevelGraphics.GetOpenGLShaderVersionHeader().c_str());

  m_IsInitialized = true;
}

void ImGuiLayerGL::OnPreDraw()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayerGL::OnPostDraw()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}