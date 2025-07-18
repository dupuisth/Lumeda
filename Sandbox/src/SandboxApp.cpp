#include <Lumeda.h>


class Sandbox : public Lumeda::Application 
{
public:
	Sandbox() 
	{

	}

	~Sandbox()
	{

	}
};

int	main() 
{
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;
}