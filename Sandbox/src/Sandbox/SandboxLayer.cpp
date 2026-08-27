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

  m_Renderer = std::make_unique<SimpleRenderer>(engine.GetGraphics().GetLowLevelGraphics());

  iGpuProgram* defaultProgram = QuickCreateProgram("default", _W("assets/shaders/default.vert"), _W("assets/shaders/default.frag"));
  iGpuProgram* screenProgram = QuickCreateProgram("core_screen", _W("assets/shaders/core_screen.vert"), _W("assets/shaders/core_screen.frag"));
  iGpuProgram* unlitProgram = QuickCreateProgram("unlit", _W("assets/shaders/unlit.vert"), _W("assets/shaders/unlit.frag"));

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
      0, 2, 1,
      0, 3, 2
    },
    {
      {0, 2, eVertexAttribType_Float},
      {1, 2, eVertexAttribType_Float}
    }
  );
  // clang-format on
  iLowLevelGraphics& llg = engine.GetGraphics().GetLowLevelGraphics();

  Material* m_ScreenMaterial = engine.GetResources().GetMaterialManager().CreateMaterial("Screen");
  m_ScreenMaterial->SetProgram(screenProgram);
  m_ScreenMaterial->GetUniformMap().SetUniform("u_ScreenTexture", &m_Renderer->GetFrameBufferColor());
  Material* m_BasicMaterial = engine.GetResources().GetMaterialManager().CreateMaterial("Basic");
  m_BasicMaterial->SetProgram(defaultProgram);

  // Load the icosphere and set the material
  Model* model = engine.GetResources().GetModelManager().CreateModel("icosphere", _W("assets/models/icosphere.fbx"));
  model->GetItems()[0].material = m_BasicMaterial;

  // Load the dirt texture and create the material
  iTexture* dirtColorTexture = engine.GetResources().GetTextureManager().CreateTexture("dirt_color", eTextureType_2D);
  dirtColorTexture->CreateFromFile(_W("assets/textures/dirt_color.jpg"));
  Material* dirtMaterial = engine.GetResources().GetMaterialManager().CreateMaterial("dirt");
  dirtMaterial->SetProgram(unlitProgram);
  dirtMaterial->GetUniformMap().SetUniform(tShaderCommonUniform_TextureDiffuse0, dirtColorTexture);

  // Load the ground and set the model
  Model* groundModel = engine.GetResources().GetModelManager().CreateModel("ground_plane", _W("assets/models/ground_plane.obj"));
  groundModel->GetItems()[0].material = dirtMaterial;

  m_World = std::make_unique<World>();

  // Ico model
  std::unique_ptr<ModelEntity> modelEntity = std::make_unique<ModelEntity>("Icosphere");
  modelEntity->SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  modelEntity->SetModel(model);
  m_World->GetRootNode().AddChild(std::move(modelEntity));

  // Ground model
  std::unique_ptr<ModelEntity> groundEntity = std::make_unique<ModelEntity>("Ground");
  groundEntity->SetModel(groundModel);
  m_World->GetRootNode().AddChild(std::move(groundEntity));

  // Player entity
  std::unique_ptr<Node> playerNode = std::make_unique<Node>("PlayerNode");

  // Camera entity
  std::unique_ptr<CameraEntity> cameraEntity = std::make_unique<CameraEntity>("Camera");
  cameraEntity->GetCamera().SetZNear(0.01f);
  cameraEntity->GetCamera().SetZFar(100.0f);
  cameraEntity->GetCamera().SetFOV(80.0f);
  cameraEntity->GetCamera().SetAspectRatio(
      (float)engine.GetGraphics().GetLowLevelGraphics().GetWidth() / (float)engine.GetGraphics().GetLowLevelGraphics().GetHeight());

  cameraEntity->SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
  m_CameraEntity = static_cast<CameraEntity*>(playerNode->AddChild(std::move(cameraEntity)));

  // PlayerController entity
  std::unique_ptr<PlayerControllerEntity> playerControllerEntity =
      std::make_unique<PlayerControllerEntity>("PlayerController", engine.GetInputs(), engine.GetTimer());
  playerNode->AddChild(std::move(playerControllerEntity));

  m_World->GetRootNode().AddChild(std::move(playerNode));
}

void SandboxLayer::Update()
{
}

void SandboxLayer::OnDraw()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  UniformMap worldUniforms;
  worldUniforms.SetUniform(tShaderCommonUniform_CameraMatrix, m_CameraEntity->GetCamera().GetProjectionView());
  m_Renderer->Submit(*m_World);

  sRenderItem renderItem = {.vertexBuffer = m_QuadBuffer.get(),
      .material = engine.GetResources().GetMaterialManager().GetResourceByName("Screen"),
      .additionalUniforms = UniformMap(),
      .featureFlags = eRenderItemFeatureFlag_ScreenSpace};
  m_Renderer->Submit(renderItem);
  m_Renderer->Flush(worldUniforms);

  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Performances"))
    {
      ImGui::LabelText("Framecount", "%zd", engine.GetTimer().GetFrameCount());
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Inputs"))
    {
      for (eKeyboardKey i = eKeyboardKey_FirstEnum; i < eKeyboardKey_LastEnum; i = (eKeyboardKey)(i + 1))
      {
        char label[8];
        sprintf(label, "%d", i);
        ImGui::LabelText(label, "%d", engine.GetInputs().GetKey(i));
      }

      ImGui::EndMenu();
    }
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

    // Maybe later on make a function to resize inside the render??
    // Or directly inside the framebuffer which will resize everything?
    m_Renderer->GetFrameBufferColor().CreateFromRawData(glm::ivec3(cevent.Width, cevent.Height, 0), ePixelFormat_RGB, nullptr);
    m_Renderer->GetFrameBufferDepthStencil().CreateFromRawData(glm::ivec3(cevent.Width, cevent.Height, 0), ePixelFormat_Depth24Stencil8, nullptr);

    m_CameraEntity->GetCamera().SetAspectRatio((float)cevent.Width / (float)cevent.Height);
  }

  return false;
}

void SandboxLayer::HandleMessage(eUpdateableMessage message)
{
  iUpdateable::HandleMessage(message);

  if (m_World != nullptr)
  {
    m_World->HandleMessage(message);
  }
}