#pragma once

#include <imgui.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/ImGui/ImGuiLayer.h>

namespace Lumeda
{
class LowLevelGraphicsGL;
class ImGuiLayerGL : public iImGuiLayer
{
public:
  ImGuiLayerGL(EventManager& eventManager, LowLevelGraphicsGL& lowLevelGraphics) :
      iImGuiLayer(), m_EventManager(eventManager), m_LowLevelGraphics(lowLevelGraphics), m_IsInitialized(false)
  {
  }
  ~ImGuiLayerGL();

  void OnStart() override;

  void OnPreDraw() override;
  void OnPostDraw() override;

private:
  EventManager& m_EventManager;
  LowLevelGraphicsGL& m_LowLevelGraphics;

  ImFont* m_DefaultFont;

  bool m_IsInitialized;
};
} // namespace Lumeda