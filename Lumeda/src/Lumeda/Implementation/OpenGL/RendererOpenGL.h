#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Window.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/UniformsMap.h>
#include <Lumeda/Renderer/Mesh.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Implementation/OpenGL/RenderCallOpenGL.h>

#include <memory>
#include <unordered_map>

namespace Lumeda
{
	struct sRenderCallMesh;
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
		const std::unordered_map<std::string, std::shared_ptr<Framebuffer>>& ListFramebuffers() override;
		const std::unordered_map<std::string, std::shared_ptr<RenderTarget>>& ListRenderTargets() override;

		std::shared_ptr<Shader> GetShader(const std::string& name) override;
		std::shared_ptr<Texture2D> GetTexture2D(const std::string& name) override;
		std::shared_ptr<Mesh> GetMesh(const std::string& name) override;
		std::shared_ptr<Material> GetMaterial(const std::string& name) override;
		std::shared_ptr<Model> GetModel(const std::string& name) override;
		std::shared_ptr<Framebuffer> GetFramebuffer(const std::string& name) override;
		std::shared_ptr<RenderTarget> GetRenderTarget(const std::string& name) override;

		std::shared_ptr<Shader> CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) override;
		std::shared_ptr<Shader> CreateShaderFromSource(const std::string& name, const char* vertexCode, const char* fragmentCode) override;
		std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, const std::string& path) override;
		std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format) override;
		std::shared_ptr<Mesh> CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) override;
		std::shared_ptr<Material> CreateMaterial(const std::string& name) override;
		std::shared_ptr<Model> CreateModel(const std::string& name) override;
		std::shared_ptr<Model> CreateModel(const std::string& name, const std::string& fromFile) override;
		std::shared_ptr<Framebuffer> CreateFramebuffer(const std::string& name) override;
		std::shared_ptr<RenderTarget> CreateRenderTarget(const std::string& name, int width, int height) override;

		void BeginFrame() override;
		void Submit(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, sUniformsMap& uniforms) override;
		void Submit(std::shared_ptr<Model> model, sUniformsMap& uniforms) override;
		void Render(std::shared_ptr<Camera> camera, std::shared_ptr<RenderTarget> renderTarget) override;
		void PrepareRenderScreen() override;
		void RenderToScreen(std::shared_ptr<RenderTarget> renderTarget, int x, int y, int width, int height) override;
		void RenderToScreen(std::shared_ptr<RenderTarget> renderTarget) override;
		void EndFrame() override;

	private:
		void OnWindowResize(Window& window, int width, int height);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures2D;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
		std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
		std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
		std::unordered_map<std::string, std::shared_ptr<Framebuffer>> m_Framebuffers;
		std::unordered_map<std::string, std::shared_ptr<RenderTarget>> m_RenderTargets;

		std::vector<sRenderCallMesh> m_RenderCallsMesh;
		std::vector<sRenderCallModel> m_RenderCallsModel;

		std::shared_ptr<Mesh> m_ScreenMesh;
		std::shared_ptr<Shader> m_ScreenShader;

		WindowCallbackToken m_WindowResizeCallbackToken;
	};
}