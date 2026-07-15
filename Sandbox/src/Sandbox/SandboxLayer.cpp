#include <imgui.h>
#include <glad/glad.h>
#include <Sandbox/SandboxBase.h>
#include <Sandbox/SandboxLayer.h>

using namespace Lumeda;
using namespace Sandbox;

iGpuProgram* QuickCreateProgram(const tString& programName, const twString& vPath, const twString& fPath)
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  iGpuShader* vertexShader = engine.GetResources().GetGpuShaderManager().CreateShader(programName + "_vert", _W(""), eShaderType_Vertex);
  vertexShader->CreateFromFile(vPath);

  iGpuShader* fragmentShader = engine.GetResources().GetGpuShaderManager().CreateShader(programName + "_frag", _W(""), eShaderType_Fragment);
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

  iGpuProgram* defaultProgram = QuickCreateProgram("default", _W("assets/shaders/default.vert"), _W("assets/shaders/default.frag"));
  iGpuProgram* screenProgram = QuickCreateProgram("core_screen", _W("assets/shaders/core_screen.vert"), _W("assets/shaders/core_screen.frag"));

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
  m_FrameBufferColor->CreateFromRawData(glm::ivec3(llg.GetWidth(), llg.GetHeight(), 0), ePixelFormat_RGB, nullptr);
  m_FrameBufferDepthStencil = llg.CreateRenderBuffer("screen_depthstencil");
  m_FrameBufferDepthStencil->SetStorage(glm::ivec2(llg.GetWidth(), llg.GetHeight()), ePixelFormat_Depth24Stencil8);
  m_FrameBuffer->AttachTexture2D(eFrameBufferAttachment_Color, *m_FrameBufferColor);
  m_FrameBuffer->AttachRenderBuffer(eFrameBufferAttachment_DepthStencil, *m_FrameBufferDepthStencil);

  m_ScreenMaterial = std::make_unique<Material>("", _W(""));
  m_ScreenMaterial->SetProgram(screenProgram);
  m_ScreenMaterial->GetUniformMap().SetUniform("u_ScreenTexture", m_FrameBufferColor.get());
  m_BasicMaterial = std::make_unique<Material>("", _W(""));
  m_BasicMaterial->SetProgram(defaultProgram);

  Model* model = engine.GetResources().GetModelManager().CreateModel("icosphere", _W("assets/models/icosphere.fbx"));
  model->GetItems()[0].material = m_BasicMaterial.get();

  m_WorldRenderer->SetFrameBuffer(m_FrameBuffer.get());

  m_World = std::make_unique<World>();

  // First triangle
  std::unique_ptr<MeshEntity> meshEntity = std::make_unique<MeshEntity>("Triangle");
  meshEntity->SetVertexBuffer(m_VertexBuffer.get());
  meshEntity->SetMaterial(m_BasicMaterial.get());
  m_World->GetRootNode().AddChild(std::move(meshEntity));

  // Second triangle
  std::unique_ptr<MeshEntity> meshEntity2 = std::make_unique<MeshEntity>("Triangle2");
  meshEntity2->SetPosition(glm::vec3(0.0f, 0.2f, 0.3f));
  meshEntity2->SetVertexBuffer(m_VertexBuffer.get());
  meshEntity2->SetMaterial(m_BasicMaterial.get());
  m_World->GetRootNode().AddChild(std::move(meshEntity2));

  // Ico model
  std::unique_ptr<ModelEntity> modelEntity = std::make_unique<ModelEntity>("Icosphere");
  modelEntity->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  modelEntity->SetModel(model);
  m_World->GetRootNode().AddChild(std::move(modelEntity));

  std::unique_ptr<CameraEntity> cameraEntity = std::make_unique<CameraEntity>("Camera");
  cameraEntity->GetCamera().SetZNear(0.01f);
  cameraEntity->GetCamera().SetZFar(100.0f);
  cameraEntity->GetCamera().SetFOV(80.0f);
  cameraEntity->GetCamera().SetAspectRatio(
      (float)engine.GetGraphics().GetLowLevelGraphics().GetWidth() / (float)engine.GetGraphics().GetLowLevelGraphics().GetHeight());

  cameraEntity->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
  m_CameraEntity = static_cast<CameraEntity*>(m_World->GetRootNode().AddChild(std::move(cameraEntity)));
}

void SandboxLayer::OnDraw()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  UniformMap worldUniforms;
  worldUniforms.SetUniform(tShaderCommonUniform_CameraMatrix, m_CameraEntity->GetCamera().GetProjectionView());
  m_WorldRenderer->Submit(*m_World);

  // Render as normal
  m_WorldRenderer->SetMode(ePolygonFace_Back, ePolygonMode_Fill);
  m_WorldRenderer->Flush(worldUniforms, false, tClearFrameBufferFlag_Color | tClearFrameBufferFlag_Depth | tClearFrameBufferFlag_Stencil);
  // Render as wireframe
  m_WorldRenderer->SetMode(ePolygonFace_FrontBack, ePolygonMode_Line);
  m_WorldRenderer->Flush(worldUniforms, true, tClearFrameBufferFlag_Depth | tClearFrameBufferFlag_Stencil);

  m_ScreenRenderer->SetMode(ePolygonFace_Back, ePolygonMode_Fill);
  m_ScreenRenderer->Submit(m_QuadBuffer.get(), m_ScreenMaterial.get(), UniformMap());
  m_ScreenRenderer->Flush(UniformMap(), true, tClearFrameBufferFlag_Color);

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Resources"))
    {
      if (ImGui::BeginMenu("Models"))
      {
        for (const auto& item : engine.GetResources().GetModelManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());

            ImGui::SeparatorText("Items");
            for (const auto& modelItem : item.second->GetItems())
            {
              ImGui::Separator();
              ImGui::LabelText("Material", (modelItem.material != nullptr) ? modelItem.material->GetName().c_str() : "NONE");
              ImGui::LabelText("VertexBuffer", (modelItem.vertexBuffer != nullptr) ? "OK" : "NONE");
            }

            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Materials"))
      {
        for (const auto& item : engine.GetResources().GetMaterialManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());
            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Textures"))
      {
        for (const auto& item : engine.GetResources().GetTextureManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());
            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Textures"))
      {
        for (const auto& item : engine.GetResources().GetTextureManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());
            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Programs"))
      {
        for (const auto& item : engine.GetResources().GetGpuProgramManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());
            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Shaders"))
      {
        for (const auto& item : engine.GetResources().GetGpuShaderManager().GetResources())
        {
          if (ImGui::BeginMenu(item.first.c_str()))
          {
            ImGui::LabelText("Label", item.second->GetName().c_str());
            ImGui::LabelText("Path", item.second->GetPath().c_str());
            ImGui::EndMenu();
          }
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
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