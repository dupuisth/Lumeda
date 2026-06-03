#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/RenderTarget.h>
#include <glm/glm.hpp>

namespace Lumeda
{
class Shader;
class Texture2D;
class Framebuffer;

class RenderTargetOpenGL : public RenderTarget
{
  public:
    RenderTargetOpenGL(const std::string& name, const glm::ivec2& size);
    virtual ~RenderTargetOpenGL();

    const std::string& GetName() const override;

    void Bind() override;
    void PrepareRender(Shader* shader);
    void UnBind() override;

    void SetSize(const glm::ivec2& size) override;
    const glm::ivec2& GetSize() const override;

    Framebuffer* GetFramebuffer() const;
    Texture2D* GetColorTexture() const;
    Texture2D* GetDepthStencilTexture() const;

  private:
    std::string m_Name;
    glm::ivec2 m_Size;

    Framebuffer* m_Framebuffer;
    Texture2D* m_ColorTexture;
    Texture2D* m_DepthStencilTexture;
};
} // namespace Lumeda