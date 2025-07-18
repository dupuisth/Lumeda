#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
	/// <summary>
	/// Represent the client application of the engine
	/// </summary>
	class LUMEDA_API IApplication
	{

	public:
		IApplication();
		virtual ~IApplication();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Terminate() = 0;
	};
}