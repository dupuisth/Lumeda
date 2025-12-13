#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>

#include <glad/glad.h>
#include <stb_image.h>

using namespace Lumeda;

Texture2DOpenGL::Texture2DOpenGL(const std::string& name, const std::string& path)
	: m_Name(name), m_Wrapping(eTextureWrapping::Repeat), m_Filtering(eTextureFiltering::Linear)
{
	LUMEDA_PROFILE;
	glGenTextures(1, &m_Handle);
	Bind();

	SetWrapping(eTextureWrapping::Repeat);
	SetFiltering(eTextureFiltering::Linear);

	int nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &(m_Size.x), &(m_Size.y), &nrChannels, 0);
	if (!data)
	{
		LUMEDA_CORE_ERROR("Failed to load image {0}", path);
		throw std::runtime_error("Failed to load image");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Size.x, m_Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture2DOpenGL::Texture2DOpenGL(const std::string& name, int width, int height, eTextureFormat format)
	: m_Size(width, height), m_Wrapping(eTextureWrapping::Repeat), m_Filtering(eTextureFiltering::Linear)
{
	LUMEDA_PROFILE;
	glGenTextures(1, &m_Handle);
	Build(width, height, format);
}

Texture2DOpenGL::~Texture2DOpenGL()
{
	LUMEDA_PROFILE;
	glDeleteTextures(1, &m_Handle);
}

void Texture2DOpenGL::Build(int width, int height, eTextureFormat format)
{
	LUMEDA_PROFILE;
	m_Size = glm::ivec2(width, height);
	Bind();

	SetWrapping(m_Wrapping);
	SetFiltering(m_Filtering);

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

eTextureWrapping Texture2DOpenGL::GetWrapping() const
{
	LUMEDA_PROFILE;
	return m_Wrapping;
}

void Texture2DOpenGL::SetWrapping(eTextureWrapping wrapping)
{
	LUMEDA_PROFILE;
	switch (wrapping)
	{
	case eTextureWrapping::Clamp:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	case eTextureWrapping::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	default:
		LUMEDA_CORE_WARN("[Texture2DOpenGL] Specified wrapping is not recognized \'{0}\'", (int)wrapping);
		return;
	}

	m_Wrapping = wrapping;
}

eTextureFiltering Texture2DOpenGL::GetFiltering() const
{
	LUMEDA_PROFILE;
	return m_Filtering;
}

void Texture2DOpenGL::SetFiltering(eTextureFiltering filtering)
{
	LUMEDA_PROFILE;
	switch (filtering)
	{
	case eTextureFiltering::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case eTextureFiltering::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	default:
		LUMEDA_CORE_WARN("[Texture2DOpenGL] Specified filtering is not recognized \'{0}\'", (int)filtering);
		return;
	}
	m_Filtering = filtering;
}

const glm::ivec2& Texture2DOpenGL::GetSize() const
{
	LUMEDA_PROFILE;
	return m_Size;
}

int Texture2DOpenGL::GetWidth() const
{
	LUMEDA_PROFILE;
	return m_Size.x;
}

int Texture2DOpenGL::GetHeight() const
{
	LUMEDA_PROFILE;
	return m_Size.y;
}

const std::string& Texture2DOpenGL::GetName() const
{
	LUMEDA_PROFILE;
	return m_Name;
}

unsigned int Texture2DOpenGL::GetOpenGLHandle()
{
	LUMEDA_PROFILE;
	return m_Handle;
}
