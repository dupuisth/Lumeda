#pragma once

#include <GLFW/glfw3.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Window.h>

namespace Lumeda
{
class WindowGLFW : public Window
{
  public:
    WindowGLFW();
    virtual ~WindowGLFW() override;

    void Update() override;

    int GetWidth() const override;
    int GetHeight() const override;
    glm::ivec2 GetSize() const override;
    float GetAspectRatio() const override;

    void SetSize(const glm::ivec2& size) const override;
    void SetMaximize() override;

    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    bool ShouldClose() const override;

    void* GetNativeWindow() const override;
    GLFWwindow* GetNativeGLFWWindow() const;

  private:
    WindowGLFW(const WindowGLFW&) = delete;
    WindowGLFW& operator=(const WindowGLFW&) = delete;
    WindowGLFW(WindowGLFW&&) = delete;
    WindowGLFW& operator=(WindowGLFW&&) = delete;

    static void GlfwWindowSizeCallback(GLFWwindow* window, int width, int height);

  private:
    GLFWwindow* m_NativeWindow;
    bool m_IsVSync;

    static std::unordered_map<GLFWwindow*, WindowGLFW*> s_Windows;
};
} // namespace Lumeda