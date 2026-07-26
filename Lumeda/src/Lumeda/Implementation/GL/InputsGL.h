#pragma once

#include <GLFW/glfw3.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Inputs/Inputs.h>

namespace Lumeda
{

class LowLevelGraphicsGL;

///////////////////////////////////////////
// Global functions
///////////////////////////////////////////
int LumedaKeyToGLFW(eKeyboardKey key);
int LumedaMouseButtonGLFW(eMouseButton button);
eKeyboardKey GLFWKeyToLumeda(int key);
eMouseButton GLFWMouseButtonToLumeda(int button);

int LumedaCursorModeToGLFW(eCursorMode mode);

struct sKeyboardKeyState
{
  eKeyboardKeyState state = eKeyboardKeyState_Up;
  size_t framecount = 0;
};

struct sMouseButtonState
{
  eMouseButtonState state = eMouseButtonState_Up;
  size_t framecount = 0;
};

struct sCursorState
{
  glm::vec2 screenPos = glm::vec2(0.0f);
  size_t framecount = 0;
};

class InputsGL : public iInputs
{
public:
  InputsGL(LowLevelGraphicsGL& lowLevelGraphics, Timer& timer);
  ~InputsGL();

  ///////////////////////////////////////////
  // Keyboard
  ///////////////////////////////////////////
  eKeyboardKeyState GetKey(eKeyboardKey key) override;

  ///////////////////////////////////////////
  // Mouse
  ///////////////////////////////////////////
  eMouseButtonState GetMouseButton(eMouseButton button) override;
  glm::vec2 GetMouseDelta() override;
  glm::vec2 GetMouseScreenPosition() override;

  ///////////////////////////////////////////
  // Cursor
  ///////////////////////////////////////////
  void SetCursorMode(eCursorMode mode) override;

private:
  ///////////////////////////////////////////
  // Static for GLFW callbacks (https://www.glfw.org/docs/3.3/input_guide.html)
  ///////////////////////////////////////////
  static void OnKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
  static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
  static void OnCursorPosCallback(GLFWwindow* window, double xPos, double yPos);

  void OnKey(int GLFWKey, int GLFWScanCode, int GLFWAction, int GLFWMods);
  void onMouseButton(int GLFWButton, int GLFWAction, int GLFWMods);
  void OnCursorPos(glm::vec2 pos);

private:
  LowLevelGraphicsGL& m_LowLevelGraphics;
  Timer& m_Timer;

  std::unordered_map<eKeyboardKey, sKeyboardKeyState> m_KeyboardState = {};
  std::unordered_map<eMouseButton, sMouseButtonState> m_MouseButtonState = {};

  sCursorState m_CursorState;
  sCursorState m_PreviousCursorState;
};
} // namespace Lumeda