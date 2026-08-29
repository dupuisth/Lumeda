#include <imgui.h>
#include <glad/glad.h>
#include <Sandbox/SandboxBase.h>
#include <Sandbox/SandboxLayer.h>

using namespace Lumeda;
using namespace Sandbox;

void SandboxLayer::OnStart()
{
  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();
  engine.GetEventManager().AddReceiver(this);

  m_Editor = std::make_unique<EditorStack>(engine);
  m_Editor->PushNodeHandler(std::make_unique<EditorDefaultNodeHandler>());
  m_Editor->PushNodeHandler(std::make_unique<EditorRotatingEntityHandler>());
  engine.GetUpdater().AddUpdateable(m_Editor.get());

  engine.GetGraphics().GetLowLevelGraphics().SetVSync(true);

  // Order is important!
  engine.GetResources().PushLoader(std::make_unique<TextureLoader>(engine.GetResources()));
  engine.GetResources().PushLoader(std::make_unique<GpuProgramLoader>(engine.GetResources()));
  engine.GetResources().PushLoader(std::make_unique<MaterialLoader>(engine.GetResources()));
  engine.GetResources().PushLoader(std::make_unique<ModelLoader>(engine.GetResources()));
  engine.GetResources().LoadAll("assets", true);

  m_Renderer = std::make_unique<SimpleRenderer>(engine.GetGraphics().GetLowLevelGraphics());

  iGpuProgram* defaultProgram = engine.GetResources().GetGpuProgramManager().GetResourceByName("default");
  iGpuProgram* screenProgram = engine.GetResources().GetGpuProgramManager().GetResourceByName("core_screen");

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
  Model* model = engine.GetResources().GetModelManager().GetResourceByName("icosphere");
  Model* groundModel = engine.GetResources().GetModelManager().GetResourceByName("ground");
  Model* armchairModel = engine.GetResources().GetModelManager().GetResourceByName("armchair");

  m_World = std::make_unique<World>();
  m_Editor->SetWorld(m_World.get());

  // Ico model
  {
    std::unique_ptr<Node> icoNode = std::make_unique<Node>("Icosphere");
    icoNode->SetLocalPosition(glm::vec3(0.0f, 0.0f, 15.0f));

    std::unique_ptr<ModelEntity> modelEntity = std::make_unique<ModelEntity>("Icosphere");
    modelEntity->SetLocalPosition(glm::vec3(0.0, -0.5f, 1.0f));
    modelEntity->SetModel(model);
    icoNode->AddChild(std::move(modelEntity));

    std::unique_ptr<RotatingEntity> rotatingEntity = std::make_unique<RotatingEntity>("Rotating", engine.GetTimer());
    rotatingEntity->SetRotating(glm::vec3(0.0f, 45.0f, 0.0f));
    icoNode->AddChild(std::move(rotatingEntity));

    m_World->GetRootNode().AddChild(std::move(icoNode));
  }

  // Armchair
  {
    std::unique_ptr<Node> armchairNode = std::make_unique<Node>("Armchair");
    std::unique_ptr<ModelEntity> modelEntity = std::make_unique<ModelEntity>("Model");
    modelEntity->SetLocalPosition(glm::vec3(0.0, -0.5f, 1.0f));
    modelEntity->SetModel(armchairModel);
    armchairNode->AddChild(std::move(modelEntity));

    m_World->GetRootNode().AddChild(std::move(armchairNode));
  }

  // Ground model
  std::unique_ptr<ModelEntity> groundEntity = std::make_unique<ModelEntity>("Ground");
  groundEntity->SetLocalPosition(glm::vec3(0.0f, -1.0f, 0.0f));
  groundEntity->SetModel(groundModel);
  m_World->GetRootNode().AddChild(std::move(groundEntity));

  // Player entity
  std::unique_ptr<Node> playerNode = std::make_unique<Node>("PlayerNode");
  playerNode->SetLocalPosition(glm::vec3(0.0f, 0.35f, -2.5f));

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
  worldUniforms.SetUniform(tShaderCommonUniform_CameraPosition, m_CameraEntity->GetCamera().GetPosition());
  worldUniforms.SetUniform(tShaderCommonUniform_CameraForward, m_CameraEntity->GetCamera().GetForward());

  tString buffer = tString(tShaderCommonUniform_MainDirectionalLight).append(".").append(tShaderCommonUniform_StructDirectionalLight_Color);
  worldUniforms.SetUniform(buffer, glm::vec3(1.0f, 1.0f, 1.0f));
  buffer = tString(tShaderCommonUniform_MainDirectionalLight).append(".").append(tShaderCommonUniform_StructDirectionalLight_Direction);
  worldUniforms.SetUniform(buffer, glm::normalize(glm::vec3(0.5f, -1.0f, 0.1f)));
  m_Renderer->Submit(*m_World);

  sRenderItem renderItem = {.vertexBuffer = m_QuadBuffer.get(),
      .material = engine.GetResources().GetMaterialManager().GetResourceByName("Screen"),
      .additionalUniforms = UniformMap(),
      .featureFlags = eRenderItemFeatureFlag_ScreenSpace};
  m_Renderer->Submit(renderItem);
  m_Renderer->Flush(worldUniforms);

  DrawImGui();
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

void SandboxLayer::DrawImGui()
{

  SandboxBase& base = GetSandboxBase();
  Engine& engine = base.GetEngine();

  // TODO: Move this.
  // Editor code, should be moved once everything is prepared
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("Performances"))
    {
      ImGui::LabelText("Framecount", "%zd", engine.GetTimer().GetFrameCount());
      ImGui::LabelText("DeltaTime", "%f", engine.GetTimer().GetDeltaTime());
      ImGui::LabelText("1/DeltaTime", "%.2f", 1.0f / engine.GetTimer().GetDeltaTime());
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

            ImGui::SeparatorText("Materials");
            for (Material* material : item.second->GetMaterials())
            {

              ImGui::LabelText("Slot", (material != nullptr ? material->GetName().c_str() : "NONE"));
            }

            ImGui::SeparatorText("Items");
            for (const auto& modelItem : item.second->GetItems())
            {
              ImGui::Separator();
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

            const char* filteringItems[]{"Nearest", "Linear"};
            int selectedItem = item.second->GetFiltering();
            if (ImGui::Combo("Filtering", &selectedItem, filteringItems, IM_ARRAYSIZE(filteringItems)))
            {
              item.second->SetFiltering((eTextureFiltering)selectedItem);
            }

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