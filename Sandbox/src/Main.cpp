#include <Lumeda.h>

#include <iostream>

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