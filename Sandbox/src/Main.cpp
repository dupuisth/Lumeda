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
		std::cout << "Initialize" << std::endl;
	}

	void Update() override
	{ 
		std::cout << "Initialize" << std::endl;
	}

	void Render() override
	{
		std::cout << "Render" << std::endl;
	}

	void Terminate() override
	{
		std::cout << "Terminate" << std::endl;
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