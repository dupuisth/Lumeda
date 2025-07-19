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

		std::shared_ptr<Lumeda::Shader> defaultShader = Lumeda::Engine::Get().GetRenderer().CreateShader("assets/shaders/default.vert", "assets/shaders/default.frag");
	}

	void Update() override
	{
	}

	void Render() override
	{
	}

	void Terminate() override
	{
		LUMEDA_TRACE("Terminate Sandbox");
	}
};

int main() 
{
	{
		Lumeda::Engine engine;
		Sandbox sandbox;
		engine.Run(sandbox);
	}
}