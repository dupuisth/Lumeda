#include <Lumeda.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <memory>

class Sandbox : public Lumeda::Layer
{
private:
	Lumeda::RenderTarget* renderTarget;

	Lumeda::RootNode* rootNode;
	Lumeda::Node* selectedNode = nullptr;
	Lumeda::Node* secondSeletedNode = nullptr;

#define FPS_VECTOR_COUNT 60
	int fpsIndex = 0;
	float fpsVector[FPS_VECTOR_COUNT];

public:
	Sandbox()
	{
		LUMEDA_PROFILE;

		for (int i = 0; i < FPS_VECTOR_COUNT; i++)
		{
			fpsVector[i] = 0.0f;
		}
		fpsIndex = 0;
	}

	~Sandbox()
	{
		LUMEDA_PROFILE;
	}

	void Initialize() override
	{
		LUMEDA_PROFILE;
		LUMEDA_TRACE("Initialized Sandbox");

		Lumeda::Engine::Get().GetWindow().SetSize(glm::ivec2(980, 500));

		Lumeda::Window& window = Lumeda::Engine::Get().GetWindow();
		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();

		renderTarget = renderer.CreateRenderTarget("RenderTarget", LUMEDA_WINDOW.GetWidth(), LUMEDA_WINDOW.GetHeight());
#ifdef LUMEDA_USE_GLAD
		Lumeda::RenderTargetOpenGL* castedRenderTarget = dynamic_cast<Lumeda::RenderTargetOpenGL*>(renderTarget);
		if (castedRenderTarget != nullptr)
		{
			castedRenderTarget->GetColorTexture()->Bind();
			castedRenderTarget->GetColorTexture()->SetFiltering(Lumeda::eTextureFiltering::Nearest);
			castedRenderTarget->GetColorTexture()->UnBind();
		}
		else
		{
			LUMEDA_WARN("Couldn't cast RenderTarget to RenderTargetOpenGL... Shouldn't happen since the backend is defined as GLAD");
		}
#endif

		Lumeda::Texture2D* defaultTexture = renderer.CreateTexture2D("redrock_Color", "assets/textures/redrock_Color.png");
		Lumeda::Shader* defaultShader = renderer.CreateShader("default", "assets/shaders/default.vert", "assets/shaders/default.frag");
		Lumeda::Material* defaultMaterial = renderer.CreateMaterial("default");
		defaultMaterial->SetShader(defaultShader);
		defaultMaterial->GetUniformsMap().Set("u_Color", defaultTexture);

		Lumeda::Texture2D* boxTexture = renderer.CreateTexture2D("box_Color", "assets/textures/box.png");
		Lumeda::Texture2D* barrelPondTexture = renderer.CreateTexture2D("barrelpond_Color", "assets/textures/barrel_pond.jpg");
		Lumeda::Texture2D* benchTexture = renderer.CreateTexture2D("bench_Color", "assets/textures/bench.jpg");
		Lumeda::Texture2D* dirtTexture = renderer.CreateTexture2D("dirt_Color", "assets/textures/dirt.jpg");
		Lumeda::Texture2D* fireTexture = renderer.CreateTexture2D("fire_Color", "assets/textures/fire_1.png");

		Lumeda::Material* boxMaterial = renderer.CreateMaterial("box");
		boxMaterial->SetShader(defaultShader);
		boxMaterial->GetUniformsMap().Set("u_Color", boxTexture);

		Lumeda::Material* barrelPondMaterial = renderer.CreateMaterial("barrelpond");
		barrelPondMaterial->SetShader(defaultShader);
		barrelPondMaterial->GetUniformsMap().Set("u_Color", barrelPondTexture);

		Lumeda::Material* fireMaterial = renderer.CreateMaterial("fire");
		fireMaterial->SetShader(defaultShader);
		fireMaterial->GetUniformsMap().Set("u_Color", fireTexture);

		Lumeda::Material* screenMaterial = renderer.CreateMaterial("screen");
		screenMaterial->SetShader(defaultShader);
#ifdef LUMEDA_USE_GLAD
		if (castedRenderTarget != nullptr)
		{
			screenMaterial->GetUniformsMap().Set("u_Color", castedRenderTarget->GetColorTexture());
		}
		else
		{
			LUMEDA_WARN("Couldn't cast RenderTarget to RenderTargetOpenGL... Shouldn't happen since the backend is defined as GLAD");
		}
#endif

		Lumeda::Model* boxModel = renderer.CreateModel("box", "assets/models/box.fbx");
		for (size_t i = 0; i < boxModel->ListItems().size(); i++)
		{
			Lumeda::ModelItem modelItem = boxModel->ListItems()[i];
			modelItem.m_Material = boxMaterial;
			boxModel->SetItem(i, modelItem);
		}

		Lumeda::Model* barrelPondModel = renderer.CreateModel("barrel_pond", "assets/models/barrel_pond.fbx");
		for (size_t i = 0; i < barrelPondModel->ListItems().size(); i++)
		{
			Lumeda::ModelItem modelItem = barrelPondModel->ListItems()[i];
			modelItem.m_Material = barrelPondMaterial;
			barrelPondModel->SetItem(i, modelItem);
		}

		Lumeda::Model* model = renderer.CreateModel("cube", "assets/models/cube.fbx");
		// Sets the material for testing
		for (size_t i = 0; i < model->ListItems().size(); i++)
		{
			Lumeda::ModelItem modelItem = model->ListItems()[i];
			modelItem.m_Material = defaultMaterial;
			model->SetItem(i, modelItem);
		}

		rootNode = LUMEDA_NEW(Lumeda::RootNode);
		Lumeda::SpinNode* cubeNode = LUMEDA_NEW(Lumeda::SpinNode, glm::vec3(0.0f, 1.00f, 0.0f));
		Lumeda::ModelNode* cubeModelNode = LUMEDA_NEW(Lumeda::ModelNode);
		Lumeda::LightNode* lightNode = LUMEDA_NEW(Lumeda::LightNode);
		lightNode->GetLight().Color = glm::vec3(1.0f);
		lightNode->GetLight().Intensity = 1.0f;
		lightNode->GetLight().LightCharacteristics = { 2.0f, 1.0f, 0.0f };
		lightNode->GetLight().LightType = Lumeda::eLightType::POINT;
		cubeModelNode->GetTransform().SetLocalPosition(glm::vec3(0.5f, 0.0f, 0.0f));
		cubeModelNode->GetTransform().SetLocalScale(glm::vec3(0.15f));
		cubeNode->AddChild(cubeModelNode);
		cubeModelNode->SetModel(*model);
		cubeNode->AddChild(lightNode);
		rootNode->AddChild(cubeNode);

		Lumeda::ModelNode* centerCubeModelNode = LUMEDA_NEW(Lumeda::ModelNode);
		centerCubeModelNode->GetTransform().SetLocalScale(glm::vec3(0.1f));
		centerCubeModelNode->SetModel(*barrelPondModel);
		rootNode->AddChild(centerCubeModelNode);

		// Playernode
		Lumeda::SpinNode* pivotNode = LUMEDA_NEW(Lumeda::SpinNode, glm::vec3(0.0f, 5.00f, 0.0f));
		Lumeda::PlayerNode* playerNode = LUMEDA_NEW(Lumeda::PlayerNode);
		playerNode->GetTransform().SetLocalPosition({ 0.0f, 0.5f, -0.8f });
		playerNode->GetTransform().SetLocalRotationEulerAngles({ 30.0f, 0.0f, 0.0f });
		// PlayerNode automatically add a CameraNode, but in order to access it, the child need to be really added, not pending.
		playerNode->ProcessLifecycle();
		Lumeda::CameraNode* cameraNode = dynamic_cast<Lumeda::CameraNode*>(playerNode->GetChildren()[0]);
		cameraNode->GetCamera()->SetCurrent();
		pivotNode->AddChild(playerNode);
		rootNode->AddChild(pivotNode);

		// Particle System
		// Benchmark
		//Lumeda::ParticleSystemNode* particleSystem = LUMEDA_NEW(Lumeda::ParticleSystemNode);
		//particleSystem->GetDescriptor().ParticleMesh = "cube_0";
		//particleSystem->GetDescriptor().ParticleMaterial = boxMaterial->GetName();
		//particleSystem->GetDescriptor().InitialVelocityXRange = { -0.1f, 0.1f };
		//particleSystem->GetDescriptor().InitialVelocityYRange = { -0.1f, 0.1f };
		//particleSystem->GetDescriptor().InitialVelocityZRange = { -0.1f, 0.1f };
		//particleSystem->GetDescriptor().InitialAngularVelocityRange = { -1.0f, 1.0f };
		//particleSystem->GetDescriptor().ParticleDelay = 0.0001f;
		//particleSystem->GetDescriptor().InitialLifetimeRange = { 0.1f, 0.3f };
		//particleSystem->GetDescriptor().InitialSizeRange = { 0.01f, 0.2f };
		//particleSystem->GetDescriptor().SetMaxParticles(2500);
		// Ok test
		Lumeda::ParticleSystemNode* particleSystem = LUMEDA_NEW(Lumeda::ParticleSystemNode);
		particleSystem->GetDescriptor().ParticleMesh = "Renderer_Quad";
		particleSystem->GetDescriptor().ParticleMaterial = fireMaterial->GetName();
		particleSystem->GetDescriptor().InitialVelocityXRange = { -0.1f, 2.0f };
		particleSystem->GetDescriptor().InitialVelocityYRange = { -0.1f, 2.5f };
		particleSystem->GetDescriptor().InitialVelocityZRange = { -0.1f, 2.0f };
		particleSystem->GetDescriptor().InitialAngularVelocityRange = { -1.0f, 1.0f };
		particleSystem->GetDescriptor().ParticleDelay = 1.0f / 5.0f;
		particleSystem->GetDescriptor().InitialLifetimeRange = { 0.5f, 4.75f };
		particleSystem->GetDescriptor().InitialSizeRange = { 0.1f, 0.2f };
		particleSystem->GetDescriptor().SetMaxParticles(2500);
		rootNode->AddChild(particleSystem);
	}

	void Update() override
	{
		LUMEDA_PROFILE;

		rootNode->ProcessLifecycle();
		rootNode->Update();
		rootNode->ProcessLifecycle();

		if (fpsIndex >= FPS_VECTOR_COUNT) fpsIndex = 0;
		fpsVector[fpsIndex++] = 1 / Lumeda::Engine::Get().GetTime().GetDeltaTime();

		float fps = 1 / Lumeda::Engine::Get().GetTime().GetDeltaTime();
		if (fps > 80.0f)
		{
			LUMEDA_TRACE("{0}", fps);
		}
	}

	void Render() override
	{
		LUMEDA_PROFILE;
		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();
		renderer.BeginFrame();
		rootNode->Render();

		Lumeda::Gizmos& gizmos = Lumeda::Engine::Get().GetGizmos();
		for (const auto& light : rootNode->GetLightNodes())
		{
			gizmos.SetColor(glm::vec4(light->GetLight().Color, 1.0f));
			gizmos.DrawCube(light->GetTransform().GetPosition(), light->GetTransform().GetRotationEulerAngles(), glm::vec3(0.1f));
		}
		gizmos.DrawGrid();

		renderer.Render(Lumeda::Camera::GetCurrent(), renderTarget);
		renderer.EndFrame();

		renderer.PrepareRenderScreen();
		renderer.RenderToScreen(renderTarget);
	}

	void RenderImGui() override
	{
		LUMEDA_PROFILE;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Infos"))
			{
#ifdef LUMEDA_PROFILING_ENABLED
				ImGui::LabelText("Profiling", "Enabled");
#else

				ImGui::LabelText("Profiling", "Disabled");
#endif // LUMEDA_PROFILING_ENABLED

				// Search the min/max FPS
				float minFps = FLT_MAX;
				float maxFps = FLT_MIN;
				float fpsAverage = 0.0f;
				for (int i = 0; i < FPS_VECTOR_COUNT; i++)
				{
					if (fpsVector[i] < minFps) minFps = fpsVector[i];
					if (fpsVector[i] > maxFps) maxFps = fpsVector[i];
					fpsAverage += fpsVector[i];
				}
				fpsAverage /= FPS_VECTOR_COUNT;

				ImGui::LabelText("Time", "%f", Lumeda::Engine::Get().GetTime().GetElapsedTime());
				ImGui::LabelText("DeltaTime", "%f", Lumeda::Engine::Get().GetTime().GetDeltaTime());
				ImGui::LabelText("FPS", "%.2f", 1 / Lumeda::Engine::Get().GetTime().GetDeltaTime());
				ImGui::LabelText("Average FPS", "%.2f", fpsAverage);
				ImGui::LabelText("Max FPS", "%.2f", maxFps);
				ImGui::LabelText("Min FPS", "%.2f", minFps);
				ImGui::LabelText("Framecount", "%lu", Lumeda::Engine::Get().GetTime().GetFrameCount());

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Resources"))
			{
				ImGui::SeparatorText("Graphics");
				RenderGraphicsResourcesMenu();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Renderer"))
			{
				ImGui::SeparatorText("Framebuffer");
				glm::ivec2 size = renderTarget->GetSize();
				if (ImGui::InputInt2("Size", glm::value_ptr(size)))
				{
					renderTarget->SetSize(size);
				}
				if (ImGui::Button("Match window size"))
				{
					glm::ivec2 size = Lumeda::Engine::Get().GetWindow().GetSize();
					renderTarget->SetSize(size);
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Camera"))
			{
				Lumeda::Camera* m_Camera = Lumeda::Camera::GetCurrent();

				if (m_Camera != nullptr)
				{
					if (ImGui::DragFloat3("Position", glm::value_ptr(m_Camera->GetTransform().GetLocalPositionRef()), 0.5f, -100.0f, 100.0f))
					{
						m_Camera->GetTransform().SetDirty();
						m_Camera->SetDirty();
					}

					glm::vec3 localRotationEuler = m_Camera->GetTransform().GetLocalRotationEulerAngles();
					if (ImGui::DragFloat3("Rotation", glm::value_ptr(localRotationEuler), 0.1f, -360.0f, 360.0f))
					{
						m_Camera->GetTransform().SetLocalRotationEulerAngles(localRotationEuler);
						m_Camera->GetTransform().SetDirty();
						m_Camera->SetDirty();
					}

					float buffer = m_Camera->GetFOV();
					if (ImGui::DragFloat("FOV", &buffer, 0.05f, 1.0f, 120.0f))
					{
						m_Camera->SetFOV(buffer);
					}

					buffer = m_Camera->GetZNear();
					if (ImGui::DragFloat("zNear", &buffer, 0.001f, 0.001f, 1.0f))
					{
						m_Camera->SetZNear(buffer);
					}

					buffer = m_Camera->GetZFar();
					if (ImGui::DragFloat("zFar", &buffer, 0.5f, 10.0f, 1000.0f))
					{
						m_Camera->SetZFar(buffer);
					}
				}
				else
				{
					ImGui::Text("No camera set");
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (ImGui::Begin("Scene"))
		{
			RenderSceneTree();
		}
		ImGui::End();

		if (selectedNode != nullptr)
		{
			if (ImGui::Begin("Selected Node"))
			{
				selectedNode->RenderImGui();
			}
			if (selectedNode->IsDestroyPending())
			{
				selectedNode = nullptr;
			}
			ImGui::End();
		}

		if (secondSeletedNode != nullptr)
		{
			if (ImGui::Begin("Second Selected Node"))
			{
				secondSeletedNode->RenderImGui();
			}
			if (secondSeletedNode->IsDestroyPending())
			{
				secondSeletedNode = nullptr;
			}
			ImGui::End();
		}
	}

	void RenderGraphicsResourcesMenu()
	{
		LUMEDA_PROFILE;
		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();
		if (ImGui::BeginMenu("Shaders"))
		{
			const auto& shaderMap = renderer.ListShaders();
			for (const auto& [name, shader] : shaderMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					ImGui::LabelText("Pointer", "%x", shader);
					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Textures"))
		{
			const auto& textureMap = renderer.ListTextures2D();
			for (const auto& [name, texture] : textureMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					ImGui::LabelText("Pointer", "%x", texture);
					ImGui::LabelText("Size", "%d x %d", texture->GetWidth(), texture->GetHeight());


					const char* filterings[] = { "NEAREST", "LINEAR" };
					int currentItem = (int)texture->GetFiltering();
					if (ImGui::BeginCombo("Filtering", filterings[currentItem]))
					{
						for (int i = 0; i < sizeof(filterings) / sizeof(char*); i++)
						{
							bool selected = currentItem == i;
							if (ImGui::Selectable(filterings[i], selected))
							{
								texture->Bind();
								texture->SetFiltering((Lumeda::eTextureFiltering)i);
							}
							if (selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
#ifdef LUMEDA_USE_GLAD
					Lumeda::Texture2DOpenGL* castedTexture = dynamic_cast<Lumeda::Texture2DOpenGL*>(texture);
					ImGui::Image((ImTextureID)(intptr_t)castedTexture->GetOpenGLHandle(), ImVec2(128, 128));
#endif

					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Mesh"))
		{
			const auto& meshMap = renderer.ListMeshes();
			for (const auto& [name, mesh] : meshMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					ImGui::LabelText("Pointer", "%x", mesh);
					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Models"))
		{
			const auto& modelMap = renderer.ListModels();
			for (const auto& [name, model] : modelMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					const auto& modelItems = model->ListItems();

					ImGui::LabelText("Pointer", "%x", model);
					if (ImGui::BeginMenu("Items"))
					{
						for (const auto& modelItem : modelItems)
						{
							std::string materialName = "nullptr";
							std::string meshName = "nullptr";

							if (modelItem.m_Material != nullptr)
							{
								materialName = modelItem.m_Material->GetName();
							}
							if (modelItem.m_Mesh != nullptr)
							{
								meshName = modelItem.m_Mesh->GetName();
							}

							ImGui::LabelText("Mesh", meshName.c_str());
							ImGui::LabelText("Material", materialName.c_str());
						}
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Materials"))
		{
			const auto& materialsMap = renderer.ListMaterials();
			for (const auto& [name, material] : materialsMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					ImGui::LabelText("Pointer", "%x", material);
					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Framebuffer"))
		{
			const auto& framebufferMap = renderer.ListFramebuffers();
			for (const auto& [name, framebuffer] : framebufferMap)
			{
				if (ImGui::BeginMenu(name.c_str()))
				{
					ImGui::LabelText("Pointer", "%x", framebuffer);
					ImGui::EndMenu();
				}
			}
			ImGui::EndMenu();
		}
	}

	void RenderSceneTree()
	{
		LUMEDA_PROFILE;

		RenderNode(rootNode);
	}

	void RenderNode(Lumeda::Node* node, int treeNodeId = 0)
	{
		LUMEDA_PROFILE;
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
		if (selectedNode == node)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}
		if (node->GetChildren().size() == 0)
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		std::string name = node->GetName() + "##" + std::to_string(treeNodeId);
		if (ImGui::TreeNodeEx(name.c_str(), flags))
		{

			if (ImGui::IsItemClicked())
			{
				selectedNode = node;
			}

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				secondSeletedNode = node;
			}

			for (auto it : node->GetChildren())
			{
				RenderNode(it, ++treeNodeId);
			}
			ImGui::TreePop();
		}
	}

	void Terminate() override
	{
		LUMEDA_PROFILE;

		LUMEDA_FREE(rootNode);
		LUMEDA_TRACE("Terminate Sandbox");
	}
};

int main()
{
	{
		Lumeda::Engine engine;
		engine.Run(LUMEDA_NEW(Sandbox));
	}
}