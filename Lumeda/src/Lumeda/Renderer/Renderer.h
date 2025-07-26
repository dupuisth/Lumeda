#pragma once

#include <Lumeda/Core/Base.h>

#include <vector>
#include <memory>

namespace Lumeda
{
	class Shader;
	class Texture;
	class Texture2D;
	class Mesh;
	struct MeshAttrib;
	class Material;
	class Model;

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;

		virtual void SetViewport(int x, int y, int width, int height)  = 0;

		virtual std::shared_ptr<Shader> CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) = 0;
		virtual std::shared_ptr<Texture2D> CreateTexture2D(const std::string& name, const std::string& path) = 0;
		virtual std::shared_ptr<Mesh> CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs) = 0;
		virtual std::shared_ptr<Material> CreateMaterial(const std::string& name) = 0;
		virtual std::shared_ptr<Model> CreateModel(const std::string& name) = 0;

		static std::unique_ptr<Renderer> Create();
	};
}