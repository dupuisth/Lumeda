#include <imgui.h>
#include <glad/glad.h>
#include <Sandbox/SandboxBase.h>
#include <Sandbox/SandboxLayer.h>

using namespace Lumeda;
using namespace Sandbox;

float r = 0.0f;

iGpuProgram* QuickCreateProgram(const tString& programName, const twString& vPath, const twString& fPath)
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  iGpuShader* vertexShader = engine.GetResources().GetGpuShaderManager().CreateShader(programName + "_vert", L"", eShaderType_Vertex);
  vertexShader->CreateFromFile(vPath);

  iGpuShader* fragmentShader = engine.GetResources().GetGpuShaderManager().CreateShader(programName + "_frag", L"", eShaderType_Fragment);
  fragmentShader->CreateFromFile(fPath);

  iGpuProgram* gpuProgram = engine.GetResources().GetGpuProgramManager().CreateProgram(programName);
  gpuProgram->AttachShader(vertexShader);
  gpuProgram->AttachShader(fragmentShader);
  gpuProgram->Link();

  return gpuProgram;
}

void SandboxLayer::OnStart()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();
  engine.GetEventManager().AddReceiver(this);

  engine.GetGraphics().GetLowLevelGraphics().SetVSync(true);

  m_WorldRenderer = std::make_unique<SimpleRenderer>(engine.GetGraphics().GetLowLevelGraphics());
  m_ScreenRenderer = std::make_unique<SimpleRenderer>(engine.GetGraphics().GetLowLevelGraphics());

  iGpuProgram* defaultProgram = QuickCreateProgram("default", L"assets/shaders/default.vert", L"assets/shaders/default.frag");
  iGpuProgram* screenProgram = QuickCreateProgram("core_screen", L"assets/shaders/core_screen.vert", L"assets/shaders/core_screen.frag");

  m_VertexBuffer = engine.GetGraphics().GetLowLevelGraphics().CreateVertexBuffer();
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

  m_QuadBuffer = engine.GetGraphics().GetLowLevelGraphics().CreateVertexBuffer();
  // clang-format off
  m_QuadBuffer->SetData(
    {
      -1.0f, -1.0f, 0.0f, 0.0f,
      -1.0f,  1.0f, 0.0f, 1.0f,
      1.0f,  1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
    }, 
    {
      0, 1, 2,
      0, 2, 3
    },
    {
      {0, 2, eVertexAttribType_Float},
      {1, 2, eVertexAttribType_Float}
    }
  );
  // clang-format on

  iLowLevelGraphics& llg = engine.GetGraphics().GetLowLevelGraphics();
  m_FrameBuffer = llg.CreateFrameBuffer("screen");
  m_FrameBufferColor = llg.CreateTexture("screen_color", eTextureType_2D, eTextureUsage_Normal);
  m_FrameBufferColor->CreateFromRawData(glm::ivec3(400, 400, 0), ePixelFormat_RGB, nullptr);
  m_FrameBufferDepthStencil = llg.CreateRenderBuffer("screen_depthstencil");
  m_FrameBufferDepthStencil->SetStorage(glm::ivec2(400, 400), ePixelFormat_Depth24Stencil8);
  m_FrameBuffer->AttachTexture2D(eFrameBufferAttachment_Color, *m_FrameBufferColor);
  m_FrameBuffer->AttachRenderBuffer(eFrameBufferAttachment_DepthStencil, *m_FrameBufferDepthStencil);

  m_ScreenMaterial = std::make_unique<Material>();
  m_ScreenMaterial->SetProgram(screenProgram);
  m_ScreenMaterial->GetUniformMap().SetUniform("u_ScreenTexture", m_FrameBufferColor.get());
  m_BasicMaterial = std::make_unique<Material>();
  m_BasicMaterial->SetProgram(defaultProgram);

  m_WorldRenderer->SetFrameBuffer(m_FrameBuffer.get());

  m_World = std::make_unique<World>();
  std::unique_ptr<MeshEntity> meshEntity = std::make_unique<MeshEntity>("Triangle");
  meshEntity->SetVertexBuffer(m_VertexBuffer.get());
  meshEntity->SetMaterial(m_BasicMaterial.get());
  m_World->GetRootNode().AddChild(std::move(meshEntity));
}

void SandboxLayer::OnDraw()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  m_WorldRenderer->Submit(*m_World);
  m_WorldRenderer->Flush(UniformMap(), true);

  m_ScreenRenderer->Submit(m_QuadBuffer.get(), m_ScreenMaterial.get(), UniformMap());
  m_ScreenRenderer->Flush(UniformMap(), true);
}

void SandboxLayer::OnPostDraw()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();
  engine.GetGraphics().GetLowLevelGraphics().SwapBuffers();
}

bool SandboxLayer::OnEvent(iEvent& event)
{
  if (event.GetType() == eGraphicsEvent_WindowFrameBufferSize)
  {
    WindowFrameBufferSizeEvent& cevent = static_cast<WindowFrameBufferSizeEvent&>(event);

    m_FrameBufferColor->CreateFromRawData(glm::ivec3(cevent.Width, cevent.Height, 0), ePixelFormat_RGB, nullptr);
    m_FrameBufferDepthStencil->SetStorage(glm::ivec2(cevent.Width, cevent.Height), ePixelFormat_Depth24Stencil8);
  }

  return false;
}