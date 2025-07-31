#include <Lumeda.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#if LUMEDA_PLATFORM_WINDOWS
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#endif

class Sandbox : public Lumeda::Layer
{
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
	}

	void Update() override
	{
		LUMEDA_PROFILE;
	}

	void Render() override
	{
		LUMEDA_PROFILE;

		Lumeda::Transform transform;
		transform.SetRotation(glm::vec3(0.0f, 0.0f, 25.0f));
		m_Model->Draw(transform.GetWorld());
	}

	void RenderImGui() override
	{
		LUMEDA_PROFILE;
		if (ImGui::BeginMainMenuBar())
		{
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