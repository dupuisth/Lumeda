#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/IApplication.h>

#include <string>

namespace Lumeda 
{
	class Engine 
	{
	public:
		Engine();
		~Engine();

		void Run(IApplication& application);

	private:
		IApplication* m_Application;
	};
}