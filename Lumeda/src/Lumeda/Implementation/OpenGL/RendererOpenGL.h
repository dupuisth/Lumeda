#pragma once

#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Core/Window.h>

namespace Lumeda
{
	class RendererOpenGL : public Renderer
	{
	public:
		RendererOpenGL();
		virtual ~RendererOpenGL();

		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;

		void SetViewport(int x, int y, int width, int height) override;

		std::shared_ptr<Shader> CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) override;
		std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, const std::string& path) override;

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures2D;
	};
}