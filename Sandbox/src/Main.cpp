#include <Lumeda.h>


class Sandbox : public Lumeda::IApplication
{
public:
	Sandbox() 
	{

	
	}

	~Sandbox()
	{

	}

	void Initialize() override
	{ 
		LUMEDA_TRACE("Initialized Sandbox");

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
	}

	void Render() override
	{
		m_Shader->Bind();
		m_Mesh->Draw();
	}

	void Terminate() override
	{
		LUMEDA_TRACE("Terminate Sandbox");
	}

	std::shared_ptr<Lumeda::Shader> m_Shader;
	std::shared_ptr<Lumeda::Mesh> m_Mesh;
};

int main() 
{
	{
		Lumeda::Engine engine;
		Sandbox sandbox;
		engine.Run(sandbox);
	}
}