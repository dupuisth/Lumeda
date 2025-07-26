#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#include <Lumeda/Implementation/OpenGL/MeshOpenGL.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/Model.h>

#include <glad/glad.h>

using namespace Lumeda;

RendererOpenGL::RendererOpenGL()
{
	LUMEDA_PROFILE;
	if (!gladLoadGL()) 
	{
		LUMEDA_CORE_CRITICAL("Failed to initialize glad");
		throw std::runtime_error("Failed to initialize glad");
	}

	m_WindowResizeCallbackToken = Engine::Get().GetWindow().AddResizeCallback(
		std::bind(&RendererOpenGL::OnWindowResize, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);
}

RendererOpenGL::~RendererOpenGL()
{
	LUMEDA_PROFILE;

	// Force delete all materials
	for (auto& material : m_Materials)
	{
		material.second.reset();
	}

	// Force delete all shaders
	for (auto& shader : m_Shaders)
	{
		shader.second.reset();
	}

	// Force delete all textures
	for (auto& texture : m_Textures2D)
	{
		texture.second.reset();
	}

	// Force delete all meshes
	for (auto& mesh : m_Meshes)
	{
		mesh.second.reset();
	}

	Engine::Get().GetWindow().RemoveResizeCallback(m_WindowResizeCallbackToken);
}

void RendererOpenGL::SetClearColor(float r, float g, float b, float a)
{
	LUMEDA_PROFILE;
	glClearColor(r, g, b, a);
}

void RendererOpenGL::Clear()
{
	LUMEDA_PROFILE;
	glClear(GL_COLOR_BUFFER_BIT);
}

void RendererOpenGL::SetViewport(int x, int y, int width, int height)
{
	LUMEDA_PROFILE;
	glViewport(x, y, width, height);
}

const std::unordered_map<std::string, std::shared_ptr<Shader>>& Lumeda::RendererOpenGL::ListShaders()
{
	LUMEDA_PROFILE;
	return m_Shaders;
}

const std::unordered_map<std::string, std::shared_ptr<Texture2D>>& Lumeda::RendererOpenGL::ListTextures2D()
{
	LUMEDA_PROFILE;
	return m_Textures2D;
}

const std::unordered_map<std::string, std::shared_ptr<Mesh>>& Lumeda::RendererOpenGL::ListMeshes()
{
	LUMEDA_PROFILE;
	return m_Meshes;
}

const std::unordered_map<std::string, std::shared_ptr<Material>>& Lumeda::RendererOpenGL::ListMaterials()
{
	LUMEDA_PROFILE;
	return m_Materials;
}

const std::unordered_map<std::string, std::shared_ptr<Model>>& Lumeda::RendererOpenGL::ListModels()
{
	LUMEDA_PROFILE;
	return m_Models;
}

#define SAFE_RETURN_RESOURCE(map, resourceName) \
const auto& iterator = map.find(resourceName); \
if (iterator == map.end()) \
{ \
	LUMEDA_CORE_WARN("[RendererOpenGL] Did not find the resource {0} in the map {1}", resourceName, #map); \
	return nullptr; \
} \
return iterator->second;

std::shared_ptr<Shader> Lumeda::RendererOpenGL::GetShader(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Shaders, name);
}

std::shared_ptr<Texture2D> Lumeda::RendererOpenGL::GetTexture2D(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Textures2D, name);
}

std::shared_ptr<Mesh> Lumeda::RendererOpenGL::GetMesh(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Meshes, name);
}

std::shared_ptr<Material> Lumeda::RendererOpenGL::GetMaterial(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Materials, name);
}

std::shared_ptr<Model> Lumeda::RendererOpenGL::GetModel(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Models, name);
}

std::shared_ptr<Shader> RendererOpenGL::CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	LUMEDA_PROFILE;
	std::shared_ptr<ShaderOpenGL> shader = std::make_shared<ShaderOpenGL>(name, vertexPath, fragmentPath);
	m_Shaders.insert({ name, shader });
	return shader;
}

std::shared_ptr<Texture2D> RendererOpenGL::CreateTexture2D(const std::string& name, const std::string& path)
{
	LUMEDA_PROFILE;
	std::shared_ptr<Texture2DOpenGL> texture2D = std::make_shared<Texture2DOpenGL>(name, path);
	m_Textures2D.insert({ name, texture2D });
	return texture2D;
}

std::shared_ptr<Mesh> RendererOpenGL::CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs)
{
	LUMEDA_PROFILE;
	std::shared_ptr<MeshOpenGL> mesh = std::make_shared<MeshOpenGL>(name, vertices, indices, attribs);
	m_Meshes.insert({ name, mesh });
	return mesh;
}

std::shared_ptr<Material> Lumeda::RendererOpenGL::CreateMaterial(const std::string& name)
{
	LUMEDA_PROFILE;
	std::shared_ptr<Material> material = std::make_shared<Material>(name);
	m_Materials.insert({ name, material });
	return material;
}

std::shared_ptr<Model> RendererOpenGL::CreateModel(const std::string& name)
{
	LUMEDA_PROFILE;
	std::shared_ptr<Model> model = std::make_shared<Model>(name);
	m_Models.insert({ name, model });
	return model;
}

void RendererOpenGL::OnWindowResize(Window& window, int width, int height)
{
	LUMEDA_PROFILE;
	SetViewport(0, 0, width, height);
}
