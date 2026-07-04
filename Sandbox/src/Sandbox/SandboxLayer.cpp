#include <Lumeda/Implementation/GL/VertexBufferGL.h>
#include <Sandbox/SandboxBase.h>
#include <Sandbox/SandboxLayer.h>

using namespace Lumeda;
using namespace Sandbox;

void SandboxLayer::OnStart()
{
  SandboxBase& base = GetSandboxBase();

  base.GetEngine().GetGraphics().GetLowLevelGraphics().SetVSync(true);

  iGpuShader* vertexShader = base.GetEngine().GetResources().GetGpuShaderManager().CreateShader("default_vert", L"", eShaderType_Vertex);
  vertexShader->CreateFromFile(L"assets/shaders/default.vert");

  iGpuShader* fragmentShader = base.GetEngine().GetResources().GetGpuShaderManager().CreateShader("default_frag", L"", eShaderType_Fragment);
  fragmentShader->CreateFromFile(L"assets/shaders/default.frag");

  iGpuProgram* gpuProgram = base.GetEngine().GetResources().GetGpuProgramManager().CreateProgram("My super GPU program!!");
  gpuProgram->AttachShader(vertexShader);
  gpuProgram->AttachShader(fragmentShader);
  gpuProgram->Link();

  m_VertexBuffer = base.GetEngine().GetGraphics().GetLowLevelGraphics().CreateVertexBuffer();
  // clang-format off
  m_VertexBuffer->SetData(
    {
      -0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f
    }, 
    {
      0, 1, 2
    },
    {
      {0, 3, eVertexAttribType_Float}
    }
  );
  // clang-format on
}

void SandboxLayer::OnDraw()
{
  SandboxBase& base = GetSandboxBase();
  iGpuProgram* gpuProgram = base.GetEngine().GetResources().GetGpuProgramManager().GetResourceByName("default_program");

  gpuProgram->Bind();
  m_VertexBuffer->Draw();
  gpuProgram->UnBind();

  gpuProgram->Reload();
}