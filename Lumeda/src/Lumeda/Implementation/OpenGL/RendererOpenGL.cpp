#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>

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
