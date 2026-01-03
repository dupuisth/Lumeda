#include <Lumeda/Renderer/Framebuffer.h>
#include <Lumeda/Core/Base.h>

namespace Lumeda
{
    class FramebufferOpenGL : public Framebuffer
    {
    public:
        FramebufferOpenGL(const std::string& name);
        virtual ~FramebufferOpenGL();

        const std::string& GetName() const override;

        void Bind() override;
        void UnBind() override;

        /// @brief Return true if the framebuffer is ready to be used, must be Bind before
        bool IsComplete();

        void AttachTexture2D(eFramebufferAttachment slot, Texture2D* texture) override;
    private:
        std::string m_Name;

        unsigned int m_Fbo;
    };
}