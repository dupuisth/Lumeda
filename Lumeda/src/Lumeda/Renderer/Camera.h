#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Transform.h>
#include <Lumeda/Core/Window.h>
#include <glm/glm.hpp>

namespace Lumeda
{
class Camera
{
  public:
    Camera(Transform* transform = nullptr);
    virtual ~Camera();

    const glm::mat4& GetProjectionView();
    const glm::mat4& GetProjection();
    const glm::mat4& GetView();

    Transform& GetTransform() { return *m_Transform; }

    float GetAspectRatio() { return m_AspectRatio; }
    float GetFOV() { return m_FOV; }
    float GetZNear() { return m_ZNear; }
    float GetZFar() { return m_ZFar; }

    void SetAspectRatio(float aspectRatio);
    void SetFOV(float fov);
    void SetZNear(float zNear);
    void SetZFar(float zFar);
    void SetDirty(bool dirty = true) { m_IsDirty = dirty; }

    static Camera* GetCurrent();
    static void SetCurrent(Camera* camera);
    void SetCurrent();

  protected:
    void OnWindowResized(Window& window, int width, int height);

    void Rebuild();

  private:
    Transform* m_Transform;
    bool m_HasTransformOwnership;

    float m_AspectRatio;
    float m_FOV;
    float m_ZNear;
    float m_ZFar;

    glm::mat4 m_ProjectionView;
    glm::mat4 m_Projection;
    glm::mat4 m_View;

    bool m_IsDirty;

    WindowCallbackToken m_WindowResizeCallbackToken;
};
} // namespace Lumeda