#pragma once

#include <string>

namespace Lumeda 
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		void TestPrint(const std::string& text);
	};
}