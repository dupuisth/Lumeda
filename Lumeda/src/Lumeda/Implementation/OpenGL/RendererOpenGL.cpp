#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>

#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>

#include <glad/glad.h>

using namespace Lumeda;

RendererOpenGL::RendererOpenGL()
{
	if (gladLoadGL() != GL_TRUE) 
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
