#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>

#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#include <Lumeda/Implementation/OpenGL/MeshOpenGL.h>

#include <glad/glad.h>

using namespace Lumeda;

RendererOpenGL::RendererOpenGL()
{
	if (!gladLoadGL()) 
	{
		LUMEDA_CORE_CRITICAL("Failed to initialize glad");
		throw std::runtime_error("Failed to initialize glad");
	}

}

RendererOpenGL::~RendererOpenGL()
{
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
}

void RendererOpenGL::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void RendererOpenGL::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RendererOpenGL::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

std::shared_ptr<Shader> RendererOpenGL::CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::shared_ptr<ShaderOpenGL> shader = std::make_shared<ShaderOpenGL>(name, vertexPath, fragmentPath);
	m_Shaders.insert({ name, shader });
	return shader;
}

std::shared_ptr<Texture2D> RendererOpenGL::CreateTexture2D(const std::string& name, const std::string& path)
{
	std::shared_ptr<Texture2DOpenGL> texture2D = std::make_shared<Texture2DOpenGL>(name, path);
	m_Textures2D.insert({ name, texture2D });
	return texture2D;
}

std::shared_ptr<Mesh> RendererOpenGL::CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs)
{
	std::shared_ptr<MeshOpenGL> mesh = std::make_shared<MeshOpenGL>(name, vertices, indices, attribs);
	m_Meshes.insert({ name, mesh });
	return mesh;
}
