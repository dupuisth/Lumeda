#include "TextureOpenGL.h"

#include <glad/glad.h>
#include <stb_image.h>

using namespace Lumeda;

Texture2DOpenGL::Texture2DOpenGL(const std::string& name, const std::string& path) : m_Name(name)
{
	LUMEDA_PROFILE;
	glGenTextures(1, &m_Handle);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SetFiltering(TextureFiltering::Linear);

	int nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &nrChannels, 0);
	if (!data)
	{
		LUMEDA_CORE_ERROR("Failed to load image {0}", path);
		throw std::runtime_error("Failed to load image");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture2DOpenGL::Texture2DOpenGL(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format)
	: m_Width(width), m_Height(height)
{
	LUMEDA_PROFILE;
	glGenTextures(1, &m_Handle);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SetFiltering(TextureFiltering::Linear);

	GLint glInternalFormat;
	GLenum glFormat;
	GLenum glDataType;
	switch (format)
	{
	case eTextureFormat::RGB:
		glInternalFormat = GL_RGB;
		glFormat = GL_RGB;
		glDataType = GL_UNSIGNED_BYTE;
		break;
	case eTextureFormat::DepthStencil:
		glInternalFormat = GL_DEPTH24_STENCIL8;
		glFormat = GL_DEPTH_STENCIL;
		glDataType = GL_UNSIGNED_INT_24_8;
		break;
	default:
		LUMEDA_CORE_WARN("[Texture2DOpenGL] Specified texture format is not recognized, using GL_RGB");
		glFormat = GL_RGB;
		glDataType = GL_UNSIGNED_BYTE;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, width, height, 0, glFormat, glDataType, nullptr);
}

Texture2DOpenGL::~Texture2DOpenGL()
{
	LUMEDA_PROFILE;
	glDeleteTextures(1, &m_Handle);
}

void Texture2DOpenGL::Bind(int slot)
{
	LUMEDA_PROFILE;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Handle);
}

void Texture2DOpenGL::UnBind()
{
	LUMEDA_PROFILE;
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2DOpenGL::SetFiltering(TextureFiltering filtering)
{
	LUMEDA_PROFILE;
	if (filtering == TextureFiltering::Nearest)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else if (filtering == TextureFiltering::Linear)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

int Texture2DOpenGL::GetWidth() const
{
	LUMEDA_PROFILE;
	return m_Width;
}

int Texture2DOpenGL::GetHeight() const
{
	LUMEDA_PROFILE;
	return m_Height;
}

unsigned int Texture2DOpenGL::GetOpenGLHandle()
{
	LUMEDA_PROFILE;
	return m_Handle;
}
