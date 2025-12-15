#include <Lumeda.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <memory>

class Sandbox : public Lumeda::Layer
{
private:
	std::shared_ptr<Lumeda::RenderTarget> renderTarget;
	std::shared_ptr<Lumeda::RenderTarget> otherRenderTarget;


	std::shared_ptr<Lumeda::RootNode> rootNode;
	Lumeda::Node* selectedNode = nullptr;
	Lumeda::Node* secondSeletedNode = nullptr;

public:
	Sandbox()
	{
		LUMEDA_PROFILE;
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

		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();

		m_Texture = renderer.CreateTexture2D("redrock_Color", "assets/textures/redrock_Color.png");
		m_Shader = renderer.CreateShader("default", "assets/shaders/default.vert", "assets/shaders/default.frag");
		m_Material = renderer.CreateMaterial("default");
		m_Material->SetShader(m_Shader);
		m_Material->GetUniformsMap().Set("u_Color", m_Texture);

		m_Model = renderer.CreateModel("quad");
		m_Model->AttachItem(
			{ m_Mesh, m_Material }
		);

		std::shared_ptr<Lumeda::Model> model = renderer.CreateModel("cube", "assets/models/cube.fbx");

		// Sets the material for testing
		for (size_t i = 0; i < model->ListItems().size(); i++)
		{
			Lumeda::ModelItem modelItem = model->ListItems()[i];
			modelItem.m_Material = m_Material;
			model->SetItem(i, modelItem);
		}

		rootNode = std::make_shared<Lumeda::RootNode>();
		std::shared_ptr<Lumeda::SpinNode> cubeNode = std::make_shared<Lumeda::SpinNode>(glm::vec3(0.0f, 0.50f, 0.0f));
		std::shared_ptr<Lumeda::ModelNode> cubeModelNode = std::make_shared<Lumeda::ModelNode>();
		std::shared_ptr<Lumeda::LightNode> lightNode = std::make_shared<Lumeda::LightNode>();
		lightNode->GetLight().Color = glm::vec3(1.0f);
		lightNode->GetLight().Intensity = 1.0f;
		lightNode->GetLight().LightCharacteristics = { 1.2f, 1.2f, 0.8f };
		lightNode->GetLight().LightType = Lumeda::eLightType::POINT;
		cubeModelNode->GetTransform().SetLocalPosition(glm::vec3(0.5f, 0.0f, 0.0f));
		cubeModelNode->GetTransform().SetLocalScale(glm::vec3(0.15f));
		cubeNode->AddChild(cubeModelNode);
		cubeModelNode->SetModel(*model);
		cubeNode->AddChild(lightNode);
		rootNode->AddChild(cubeNode);

		std::shared_ptr<Lumeda::ModelNode> centerCubeModelNode = std::make_shared<Lumeda::ModelNode>();
		centerCubeModelNode->GetTransform().SetLocalScale(glm::vec3(0.1f));
		centerCubeModelNode->SetModel(*model);
		rootNode->AddChild(centerCubeModelNode);

		// Playernode
		std::shared_ptr<Lumeda::SpinNode> pivotNode = std::make_shared<Lumeda::SpinNode>(glm::vec3(0.2f, 0.05f, 0.1f));
		std::shared_ptr<Lumeda::PlayerNode> playerNode = std::make_shared<Lumeda::PlayerNode>();
		playerNode->GetTransform().SetLocalPosition({ 0.0f, 0.5f, -0.8f });
		playerNode->GetTransform().SetLocalRotationEulerAngles({ 30.0f, 0.0f, 0.0f });
		// PlayerNode automatically add a CameraNode, but in order to access it, the child need to be really added, not pending.
		playerNode->ProcessLifecycle();
		std::shared_ptr<Lumeda::CameraNode> cameraNode = std::dynamic_pointer_cast<Lumeda::CameraNode>(playerNode->GetChildren()[0]);
		cameraNode->GetCamera()->SetCurrent();

		pivotNode->AddChild(playerNode);
		rootNode->AddChild(pivotNode);

		renderTarget = renderer.CreateRenderTarget("RenderTarget", 600, 400);
		otherRenderTarget = renderer.CreateRenderTarget("RenderTarget_half", 100, 100);
	}

	void Update() override
	{
		LUMEDA_PROFILE;

		rootNode->ProcessLifecycle();
		rootNode->Update();
	}

	void Render() override
	{
		LUMEDA_PROFILE;

		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();
		renderer.BeginFrame();
		rootNode->Render();
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
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Camera"))
			{
				std::shared_ptr<Lumeda::Camera> m_Camera = Lumeda::Camera::GetCurrent();

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
			ImGui::End();
		}

		if (selectedNode != nullptr)
		{
			if (ImGui::Begin("Selected Node"))
			{
				selectedNode->RenderImGui();
			}
			ImGui::End();
		}

		if (secondSeletedNode != nullptr)
		{
			if (ImGui::Begin("Second Selected Node"))
			{
				secondSeletedNode->RenderImGui();
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
					std::shared_ptr<Lumeda::Texture2DOpenGL> castedTexture = std::dynamic_pointer_cast<Lumeda::Texture2DOpenGL>(texture);
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

		RenderNode(rootNode.get());
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
				RenderNode(it.get(), ++treeNodeId);
			}
			ImGui::TreePop();
		}
	}

	void Terminate() override
	{
		LUMEDA_PROFILE;
		LUMEDA_TRACE("Terminate Sandbox");
	}

	std::shared_ptr<Lumeda::Material> m_Material;
	std::shared_ptr<Lumeda::Shader> m_Shader;
	std::shared_ptr<Lumeda::Mesh> m_Mesh;
	std::shared_ptr<Lumeda::Texture2D> m_Texture;
	std::shared_ptr<Lumeda::Model> m_Model;
};

int main()
{
	{
		Lumeda::Engine engine;
		engine.Run(std::make_unique<Sandbox>());
	}
}