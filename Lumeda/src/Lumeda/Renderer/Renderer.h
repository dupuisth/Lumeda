#pragma once

#include <Lumeda/Core/Base.h>

#include <memory>

namespace Lumeda
{
	class Renderer
	{
	public:
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void SetViewport(int x, int y, int width, int height)  = 0;

		static std::unique_ptr<Renderer> Create();
	};
}