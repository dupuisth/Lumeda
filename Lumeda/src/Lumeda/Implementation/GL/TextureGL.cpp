#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>
#include <Lumeda/Implementation/GL/TextureGL.h>

using namespace Lumeda;

TextureGL::TextureGL(const tString& name, eTextureType type, eTextureUsage usage, iLowLevelGraphics& lowLevelGraphics) :
    iTexture(name, type, usage, lowLevelGraphics), m_HandleGL(0), m_LowLevelGraphicsGL(static_cast<LowLevelGraphicsGL&>(lowLevelGraphics))
{
}

TextureGL::~TextureGL()
{
    if (HasData())
    {
        glDeleteTextures(1, &m_HandleGL);
    }
}

void TextureGL::CreateFromRawData(const glm::ivec3& size, ePixelFormat pixelFormat, unsigned char* data)
{
    if (HasData())
    {
        return;
    }

    m_Size = size;
    m_PixelFormat = pixelFormat;

    glGenTextures(1, &m_HandleGL);
    GLenum GLTarget = TextureTypeToGLTarget(m_Type);
    glBindTexture(GLTarget, m_HandleGL);

    CopyTextureDataToGL(data);
    ApplyProperties();
    glGenerateMipmap(GLTarget);

    glBindTexture(GLTarget, 0);
}

void TextureGL::SetWrapping(eTextureWrapping wrapping)
{
    m_Wrapping = wrapping;
    ApplyProperties();
}

void TextureGL::SetFiltering(eTextureFiltering filtering)
{
    m_Filtering = filtering;
    ApplyProperties();
}

void TextureGL::CopyTextureDataToGL(unsigned char* data)
{
    GLenum GLTarget = TextureTypeToGLTarget(m_Type);
    GLenum GLFormat = PixelFormatToGLFormat(m_PixelFormat);
    GLenum GLInternalFormat = PixelFormatToGLInternalFormat(m_PixelFormat);
    GLenum GLType = GL_UNSIGNED_BYTE;

    if (m_Type == eTextureType_1D)
    {
        glTexImage1D(GLTarget, 0, GLInternalFormat, m_Size.x, 0, GLFormat, GLType, data);
    }
    else if (m_Type == eTextureType_2D)
    {
        glTexImage2D(GLTarget, 0, GLInternalFormat, m_Size.x, m_Size.y, 0, GLFormat, GLType, data);
    }
    else if (m_Type == eTextureType_3D)
    {
        glTexImage3D(GLTarget, 0, GLInternalFormat, m_Size.x, m_Size.y, m_Size.z, 0, GLFormat, GLType, data);
    }
}

void TextureGL::ApplyProperties()
{
    if (!HasData())
    {
        return;
    }

    GLenum GLTarget = TextureTypeToGLTarget(m_Type);
    GLenum GLWrapping = WrappingToGLWrapping(m_Wrapping);
    GLenum GLFiltering = FilteringToGLFiltering(m_Filtering);

    glBindTexture(GLTarget, m_HandleGL);

    glTexParameteri(GLTarget, GL_TEXTURE_WRAP_S, GLWrapping);
    glTexParameteri(GLTarget, GL_TEXTURE_WRAP_T, GLWrapping);
    glTexParameteri(GLTarget, GL_TEXTURE_WRAP_R, GLWrapping);

    glTexParameteri(GLTarget, GL_TEXTURE_MIN_FILTER, GLFiltering);
    glTexParameteri(GLTarget, GL_TEXTURE_MAG_FILTER, GLFiltering);

    glBindTexture(GLTarget, 0);
}