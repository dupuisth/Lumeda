#include <Lumeda/Renderer/Framebuffer.h>

namespace Lumeda
{
    class FramebufferOpenGL : public Framebuffer
    {
    public:
        FramebufferOpenGL(const std::string& name);
        virtual ~FramebufferOpenGL();

        const std::string& GetName() const override;
    private:
        std::string m_Name;
    };
}