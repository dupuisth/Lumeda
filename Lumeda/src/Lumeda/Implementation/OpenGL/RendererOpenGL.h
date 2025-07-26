#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Core/Window.h>

#include <memory>
#include <unordered_map>

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

		const std::unordered_map<std::string, std::shared_ptr<Shader>>& ListShaders() override;
		const std::unordered_map<std::string, std::shared_ptr<Texture2D>>& ListTextures2D() override;
		const std::unordered_map<std::string, std::shared_ptr<Mesh>>& ListMeshes() override;
		const std::unordered_map<std::string, std::shared_ptr<Material>>& ListMaterials() override;
		const std::unordered_map<std::string, std::shared_ptr<Model>>& ListModels() override;

		std::shared_ptr<Shader> GetShader(const std::string& name) override;
		std::shared_ptr<Texture2D> GetTexture2D(const std::string& name) override;
		std::shared_ptr<Mesh> GetMesh(const std::string& name) override;
		std::shared_ptr<Material> GetMaterial(const std::string& name) override;
		std::shared_ptr<Model> GetModel(const std::string& name) override;

		std::shared_ptr<Shader> CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) override;
		std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, const std::string& path) override;
		std::shared_ptr<Mesh> CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) override;
		std::shared_ptr<Material> CreateMaterial(const std::string& name) override;
		std::shared_ptr<Model> CreateModel(const std::string& name) override;

	private:
		void OnWindowResize(Window& window, int width, int height);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures2D;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
		std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
		std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;

		WindowCallbackToken m_WindowResizeCallbackToken;
	};
}