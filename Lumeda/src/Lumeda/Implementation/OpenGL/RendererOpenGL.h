#pragma once

#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Core/Window.h>

namespace Lumeda
{
	class RendererOpenGL : public Renderer
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();

		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;

		void SetViewport(int x, int y, int width, int height) override;
	};
}