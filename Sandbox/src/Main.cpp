#include <Lumeda.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#if LUMEDA_PLATFORM_WINDOWS | LUMEDA_PLATFORM_LINUX
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#endif

class Sandbox : public Lumeda::Layer
{
private:
	Lumeda::Node headNode;
	Lumeda::Node* selectedNode = nullptr;

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

		Lumeda::Camera::SetCurrent(m_Camera);

		Lumeda::Renderer& renderer = Lumeda::Engine::Get().GetRenderer();

		m_Camera.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -0.2f));
		m_Shader = renderer.CreateShader("default", "assets/shaders/default.vert", "assets/shaders/default.frag");
		m_Mesh = renderer.CreateMesh(
			"quad",
			{
				-0.5f, -0.5f, 0.0f, -1.0f, 1.0f, // Top Left
				-0.5f, 0.5f, 0.0f, -1.0f, 0.0f,  // Bottom Left
				0.5f, -0.5f, 0.0f, 1.0f, 1.0f,   // Top Right
				0.5f, 0.5f, 0.0f, 1.0f, 0.0f     // Bottom Right
			},
			{
				0, 1, 2,
				1, 2, 3
			},
			{
				{ 0, 3, Lumeda::MeshAttribType::FLOAT },
				{ 1, 2, Lumeda::MeshAttribType::FLOAT }
			}
		);
		m_Texture = renderer.CreateTexture2D("redrock_Color", "assets/textures/redrock_Color.png");

		m_Material = renderer.CreateMaterial("default");
		m_Material->SetShader(m_Shader);
		m_Material->SetUniform("u_Color", m_Texture);

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

		std::shared_ptr<Lumeda::SpinNode> cubeNode = std::make_shared<Lumeda::SpinNode>(glm::vec3(0.0f, 0.1f, 0.0f));
		std::shared_ptr<Lumeda::ModelNode> cubeModelNode = std::make_shared<Lumeda::ModelNode>();
		cubeNode->AddChild(cubeModelNode);
		cubeModelNode->SetModel(*model);
		headNode.AddChild(cubeNode);
	}

	void Update() override
	{
		LUMEDA_PROFILE;

		headNode.ProcessLifecycle();
		headNode.Update();
	}

	void Render() override
	{
		LUMEDA_PROFILE;

		headNode.Render();
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

			if (ImGui::BeginMenu("Renderer"))
			{
				ImGui::SeparatorText("Resources");
				RenderResourceMenu();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Camera"))
			{
				if (ImGui::DragFloat3("Position", glm::value_ptr(m_Camera.GetTransform().GetPositionRef()), 0.5f, -100.0f, 100.0f))
				{
					m_Camera.GetTransform().SetDirty();
					m_Camera.SetDirty();
				}

				if (ImGui::DragFloat3("Rotation", glm::value_ptr(m_Camera.GetTransform().GetRotationRef()), 0.1f, -360.0f, 360.0f))
				{
					m_Camera.GetTransform().SetDirty();
					m_Camera.SetDirty();
				}

				float buffer = m_Camera.GetFOV();
				if (ImGui::DragFloat("FOV", &buffer, 0.05f, 1.0f, 120.0f))
				{
					m_Camera.SetFOV(buffer);
				}

				buffer = m_Camera.GetZNear();
				if (ImGui::DragFloat("zNear", &buffer, 0.001f, 0.001f, 1.0f))
				{
					m_Camera.SetZNear(buffer);
				}

				buffer = m_Camera.GetZFar();
				if (ImGui::DragFloat("zFar", &buffer, 0.5f, 10.0f, 1000.0f))
				{
					m_Camera.SetZFar(buffer);
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
	}

	void RenderResourceMenu()
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
					
#if LUMEDA_PLATFORM_WINDOWS
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
	}

	void RenderSceneTree()
	{
		LUMEDA_PROFILE;

		if (ImGui::TreeNodeEx("root", ImGuiTreeNodeFlags_DefaultOpen))
		{
			RenderNode(&headNode);
			ImGui::TreePop();
		}
	}

	void RenderNode(Lumeda::Node* node)
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

		if (ImGui::TreeNodeEx(node->GetName().c_str(), flags))
		{

			if (ImGui::IsItemClicked())
			{
				selectedNode = node;
			}

			for (auto it : node->GetChildren())
			{
				RenderNode(it.get());
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
	Lumeda::Camera m_Camera;
};

int main() 
{
	{
		Lumeda::Engine engine;
		engine.Run(std::make_unique<Sandbox>());
	}
}