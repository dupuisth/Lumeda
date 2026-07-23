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

struct sKeyboardKeyState
{
  eKeyboardKeyState state;
  size_t framecount;
};

struct sMouseButtonState
{
  eMouseButtonState state;
  size_t framecount;
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

private:
  ///////////////////////////////////////////
  // Static for GLFW callbacks
  ///////////////////////////////////////////
  static void OnKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
  static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

  void OnKey(int GLFWKey, int GLFWScanCode, int GLFWAction, int GLFWMods);
  void onMouseButton(int GLFWButton, int GLFWAction, int GLFWMods);

private:
  LowLevelGraphicsGL& m_LowLevelGraphics;
  Timer& m_Timer;

  std::unordered_map<eKeyboardKey, sKeyboardKeyState> m_KeyboardState = {};
  std::unordered_map<eMouseButton, sMouseButtonState> m_MouseButtonState = {};
};
} // namespace Lumeda