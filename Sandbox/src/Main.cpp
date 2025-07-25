#include <Lumeda.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

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
		m_Camera.GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -0.2f));
		m_Shader = Lumeda::Engine::Get().GetRenderer().CreateShader("default", "assets/shaders/default.vert", "assets/shaders/default.frag");
		m_Mesh = Lumeda::Engine::Get().GetRenderer().CreateMesh(
			"quad",
			{
				-0.5f, -0.5f, 0.0f, // Top Left
				-0.5f, 0.5f, 0.0f, // Bottom Left
				0.5f, -0.5f, 0.0f, // Top Right
				0.5f, 0.5f, 0.0f, // Bottom Right
			},
			{
				0, 1, 2,
				1, 2, 3
			},
			{
				{ 0, 3, Lumeda::MeshAttribType::FLOAT }
			}
		);
	}

	void Update() override
	{
		LUMEDA_PROFILE;
	}

	void Render() override
	{
		LUMEDA_PROFILE;
		m_Shader->Bind();
		m_Shader->SetUniform("u_Camera", m_Camera.GetProjectionView());
		m_Mesh->Draw();
	}

	void RenderImGui() override
	{
		LUMEDA_PROFILE;

		if (ImGui::BeginMainMenuBar())
		{
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

	void Terminate() override
	{
		LUMEDA_PROFILE;
		LUMEDA_TRACE("Terminate Sandbox");
	}

	std::shared_ptr<Lumeda::Shader> m_Shader;
	std::shared_ptr<Lumeda::Mesh> m_Mesh;
	Lumeda::Camera m_Camera;
};

int main() 
{
	{
		Lumeda::Engine engine;
		engine.Run(std::make_unique<Sandbox>());
	}
}