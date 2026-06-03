#include <Lumeda/Core/Engine.h>
#include <Lumeda/Implementation/OpenGL/FramebufferOpenGL.h>
#include <Lumeda/Implementation/OpenGL/RenderTargetOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#include <Lumeda/Renderer/Framebuffer.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Texture.h>

using namespace Lumeda;

RenderTargetOpenGL::RenderTargetOpenGL(const std::string& name, const glm::ivec2& size) : m_Size(size), m_Name(name)
{
    LUMEDA_PROFILE;
    static std::atomic<uint64_t> renderTargetCounter{0};
    Renderer& renderer = Engine::Get().GetRenderer();
    m_Framebuffer = renderer.CreateFramebuffer("RenderTarget_Framebuffer_" + std::to_string(renderTargetCounter));
    m_ColorTexture =
        renderer.CreateTexture2D("RenderTarget_ColorTexture_" + std::to_string(renderTargetCounter), size.x, size.y, eTextureFormat::RGB);
    m_DepthStencilTexture = renderer.CreateTexture2D(
        "RenderTarget_DepthStencilTexture_" + std::to_string(renderTargetCounter), size.x, size.y, eTextureFormat::DepthStencil);
    m_Framebuffer->Bind();
    m_Framebuffer->AttachTexture2D(eFramebufferAttachment::ColorAttachment, m_ColorTexture);
    m_Framebuffer->AttachTexture2D(eFramebufferAttachment::DepthStencilAttachment, m_DepthStencilTexture);
    m_Framebuffer->UnBind();
    renderTargetCounter++;

    if (!static_cast<FramebufferOpenGL*>(m_Framebuffer)->IsComplete())
    {
        LUMEDA_CORE_ERROR("[RenderTargetOpenGL] Framebuffer not ready, something went wrong when initializing");
    }
}

RenderTargetOpenGL::~RenderTargetOpenGL()
{
    LUMEDA_PROFILE;
    Renderer& renderer = Engine::Get().GetRenderer();
    renderer.DeleteFramebuffer(m_Framebuffer);
    renderer.DeleteTexture2D(m_ColorTexture);
    renderer.DeleteTexture2D(m_DepthStencilTexture);
}

const std::string& RenderTargetOpenGL::GetName() const
{
    LUMEDA_PROFILE;
    return m_Name;
}

void RenderTargetOpenGL::Bind()
{
    LUMEDA_PROFILE;
    m_Framebuffer->Bind();
}

void RenderTargetOpenGL::PrepareRender(Shader* shader)
{
    LUMEDA_PROFILE;
    shader->Bind();
    shader->SetUniform("u_ColorTexture", 0);
    m_ColorTexture->Bind(0);
    shader->SetUniform("u_DepthStencilTexture", 1);
    m_DepthStencilTexture->Bind(1);
}

void RenderTargetOpenGL::UnBind()
{
    LUMEDA_PROFILE;
    m_Framebuffer->UnBind();
}

void RenderTargetOpenGL::SetSize(const glm::ivec2& size)
{
    LUMEDA_PROFILE;
    m_Size = size;

    Texture2DOpenGL* colorTexture = static_cast<Texture2DOpenGL*>(m_ColorTexture);
    colorTexture->Build(size.x, size.y, eTextureFormat::RGB);

    Texture2DOpenGL* depthStencilTexture = static_cast<Texture2DOpenGL*>(m_DepthStencilTexture);
    depthStencilTexture->Build(size.x, size.y, eTextureFormat::DepthStencil);
}

const glm::ivec2& RenderTargetOpenGL::GetSize() const
{
    LUMEDA_PROFILE;
    return m_Size;
}

Framebuffer* RenderTargetOpenGL::GetFramebuffer() const
{
    LUMEDA_PROFILE;
    return m_Framebuffer;
}

Texture2D* RenderTargetOpenGL::GetColorTexture() const
{
    LUMEDA_PROFILE;
    return m_ColorTexture;
}

Texture2D* RenderTargetOpenGL::GetDepthStencilTexture() const
{
    LUMEDA_PROFILE;
    return m_DepthStencilTexture;
}
