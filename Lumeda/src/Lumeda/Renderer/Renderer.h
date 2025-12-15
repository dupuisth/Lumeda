#pragma once

#include <Lumeda/Core/Base.h>

#include <vector>
#include <memory>
#include <unordered_map>

namespace Lumeda
{
	class Camera;
	class Shader;
	class Texture;
	class Texture2D;
	class Mesh;
	struct MeshAttrib;
	class Material;
	class Model;
	class Framebuffer;
	class RenderTarget;

	struct sUniformsMap;
	enum class eTextureFormat;

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		// Lists
		virtual const std::unordered_map<std::string, std::shared_ptr<Shader>>& ListShaders() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<Texture2D>>& ListTextures2D() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<Mesh>>& ListMeshes() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<Material>>& ListMaterials() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<Model>>& ListModels() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<Framebuffer>>& ListFramebuffers() = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<RenderTarget>>& ListRenderTargets() = 0;

		// Gets
		virtual std::shared_ptr<Shader> GetShader(const std::string& name) = 0;
		virtual std::shared_ptr<Texture2D> GetTexture2D(const std::string& name) = 0;
		virtual std::shared_ptr<Mesh> GetMesh(const std::string& name) = 0;
		virtual std::shared_ptr<Material> GetMaterial(const std::string& name) = 0;
		virtual std::shared_ptr<Model> GetModel(const std::string& name) = 0;
		virtual std::shared_ptr<Framebuffer> GetFramebuffer(const std::string& name) = 0;
		virtual std::shared_ptr<RenderTarget> GetRenderTarget(const std::string& name) = 0;

		// Creates
		virtual std::shared_ptr<Shader> CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) = 0;
		virtual std::shared_ptr<Shader> CreateShaderFromSource(const std::string& name, const char* vertexCode, const char* fragmentCode) = 0;
		virtual std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, const std::string& path) = 0;
		virtual std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format) = 0;
		virtual std::shared_ptr<Mesh> CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) = 0;
		virtual std::shared_ptr<Material> CreateMaterial(const std::string& name) = 0;
		virtual std::shared_ptr<Model> CreateModel(const std::string& name) = 0;
		virtual std::shared_ptr<Model> CreateModel(const std::string& name, const std::string& fromFile) = 0;
		virtual std::shared_ptr<Framebuffer> CreateFramebuffer(const std::string& name) = 0;
		virtual std::shared_ptr<RenderTarget> CreateRenderTarget(const std::string& name, int width, int height) = 0;

		virtual void BeginFrame() = 0;
		virtual void Submit(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, sUniformsMap& uniforms) = 0;
		virtual void Submit(std::shared_ptr<Model> model, sUniformsMap& uniforms) = 0;
		virtual void Render(std::shared_ptr<Camera> camera, std::shared_ptr<RenderTarget> renderTarget) = 0;
		virtual void PrepareRenderScreen() = 0;
		virtual void RenderToScreen(std::shared_ptr<RenderTarget> renderTarget, int x, int y, int width, int height) = 0;
		virtual void RenderToScreen(std::shared_ptr<RenderTarget> renderTarget) = 0;
		virtual void EndFrame() = 0;

		static std::unique_ptr<Renderer> Create();
	};
}