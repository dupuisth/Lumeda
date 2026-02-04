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

		const std::unordered_map<std::string, Shader*>& ListShaders() override;
		const std::unordered_map<std::string, Texture2D*>& ListTextures2D() override;
		const std::unordered_map<std::string, Mesh*>& ListMeshes() override;
		const std::unordered_map<std::string, Material*>& ListMaterials() override;
		const std::unordered_map<std::string, Model*>& ListModels() override;
		const std::unordered_map<std::string, Framebuffer*>& ListFramebuffers() override;
		const std::unordered_map<std::string, RenderTarget*>& ListRenderTargets() override;

		Shader* GetShader(const std::string& name) override;
		Texture2D* GetTexture2D(const std::string& name) override;
		Mesh* GetMesh(const std::string& name) override;
		Material* GetMaterial(const std::string& name) override;
		Model* GetModel(const std::string& name) override;
		Framebuffer* GetFramebuffer(const std::string& name) override;
		RenderTarget* GetRenderTarget(const std::string& name) override;

		Shader* CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) override;
		Shader* CreateShaderFromSource(const std::string& name, const char* vertexCode, const char* fragmentCode) override;
		Texture2D* CreateTexture2D(const std::string& name, const std::string& path) override;
		Texture2D* CreateTexture2D(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format) override;
		Mesh* CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) override;
		Material* CreateMaterial(const std::string& name) override;
		Model* CreateModel(const std::string& name) override;
		Model* CreateModel(const std::string& name, const std::string& fromFile) override;
		Framebuffer* CreateFramebuffer(const std::string& name) override;
		RenderTarget* CreateRenderTarget(const std::string& name, int width, int height) override;

		void DeleteShader(Shader* shader) override;
		void DeleteTexture2D(Texture2D* texture) override;
		void DeleteMesh(Mesh* mesh) override;
		void DeleteMaterial(Material* material) override;
		void DeleteModel(Model* model) override;
		void DeleteFramebuffer(Framebuffer* framebuffer) override;
		void DeleteRenderTarget(RenderTarget* renderTarget) override;

		void BeginFrame() override;
		void Submit(Mesh* mesh, Material* material, sUniformsMap& uniforms) override;
		void Submit(Model* model, sUniformsMap& uniforms) override;
		void Submit(sParticleSystemDescriptor* particleSystem) override;
		void Render(Camera* camera, RenderTarget* renderTarget) override;
		void PrepareRenderScreen() override;
		void RenderToScreen(RenderTarget* renderTarget, int x, int y, int width, int height) override;
		void RenderToScreen(RenderTarget* renderTarget) override;
		void EndFrame() override;

	private:
		void OnWindowResize(Window& window, int width, int height);

	private:
		std::unordered_map<std::string, Shader*> m_Shaders;
		std::unordered_map<std::string, Texture2D*> m_Textures2D;
		std::unordered_map<std::string, Mesh*> m_Meshes;
		std::unordered_map<std::string, Material*> m_Materials;
		std::unordered_map<std::string, Model*> m_Models;
		std::unordered_map<std::string, Framebuffer*> m_Framebuffers;
		std::unordered_map<std::string, RenderTarget*> m_RenderTargets;

		std::vector<sRenderCallMesh> m_RenderCallsMesh;
		std::vector<sRenderCallMesh> m_RenderCallsMeshTransparent;
		std::vector<sRenderCallModel> m_RenderCallsModel;

		Mesh* m_ScreenMesh;
		Shader* m_ScreenShader;

		WindowCallbackToken m_WindowResizeCallbackToken;
	};
}