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
		virtual const std::unordered_map<std::string, Shader*>& ListShaders() = 0;
		virtual const std::unordered_map<std::string, Texture2D*>& ListTextures2D() = 0;
		virtual const std::unordered_map<std::string, Mesh*>& ListMeshes() = 0;
		virtual const std::unordered_map<std::string, Material*>& ListMaterials() = 0;
		virtual const std::unordered_map<std::string, Model*>& ListModels() = 0;
		virtual const std::unordered_map<std::string, Framebuffer*>& ListFramebuffers() = 0;
		virtual const std::unordered_map<std::string, RenderTarget*>& ListRenderTargets() = 0;

		// Gets
		virtual Shader* GetShader(const std::string& name) = 0;
		virtual Texture2D* GetTexture2D(const std::string& name) = 0;
		virtual Mesh* GetMesh(const std::string& name) = 0;
		virtual Material* GetMaterial(const std::string& name) = 0;
		virtual Model* GetModel(const std::string& name) = 0;
		virtual Framebuffer* GetFramebuffer(const std::string& name) = 0;
		virtual RenderTarget* GetRenderTarget(const std::string& name) = 0;

		// Creates
		virtual Shader* CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) = 0;
		virtual Shader* CreateShaderFromSource(const std::string& name, const char* vertexCode, const char* fragmentCode) = 0;
		virtual Texture2D* CreateTexture2D(const std::string& name, const std::string& path) = 0;
		virtual Texture2D* CreateTexture2D(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format) = 0;
		virtual Mesh* CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) = 0;
		virtual Material* CreateMaterial(const std::string& name) = 0;
		virtual Model* CreateModel(const std::string& name) = 0;
		virtual Model* CreateModel(const std::string& name, const std::string& fromFile) = 0;
		virtual Framebuffer* CreateFramebuffer(const std::string& name) = 0;
		virtual RenderTarget* CreateRenderTarget(const std::string& name, int width, int height) = 0;

		virtual void DeleteShader(Shader* shader) = 0;
		virtual void DeleteTexture2D(Texture2D* texture) = 0;
		virtual void DeleteMesh(Mesh* mesh) = 0;
		virtual void DeleteMaterial(Material* material) = 0;
		virtual void DeleteModel(Model* model) = 0;
		virtual void DeleteFramebuffer(Framebuffer* framebuffer) = 0;
		virtual void DeleteRenderTarget(RenderTarget* renderTarget) = 0;

		virtual void BeginFrame() = 0;
		virtual void Submit(Mesh* mesh, Material* material, sUniformsMap& uniforms) = 0;
		virtual void Submit(Model* model, sUniformsMap& uniforms) = 0;
		virtual void Render(Camera* camera, RenderTarget* renderTarget) = 0;
		virtual void PrepareRenderScreen() = 0;
		virtual void RenderToScreen(RenderTarget* renderTarget, int x, int y, int width, int height) = 0;
		virtual void RenderToScreen(RenderTarget* renderTarget) = 0;
		virtual void EndFrame() = 0;

		static Renderer* Create();
	};
}