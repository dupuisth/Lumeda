#include <stde/bimap.hpp>
#include <Lumeda/Engine/Timer.h>
#include <Lumeda/Implementation/GL/InputsGL.h>
#include <Lumeda/Implementation/GL/LowLevelGraphicsGL.h>

using namespace Lumeda;

stde::bimap<eKeyboardKey, int> LumedaGLFWKeyboardKeyMapping = {
    {eKeyboardKey_A, GLFW_KEY_A},
    {eKeyboardKey_B, GLFW_KEY_B},
    {eKeyboardKey_C, GLFW_KEY_C},
    {eKeyboardKey_D, GLFW_KEY_D},
    {eKeyboardKey_E, GLFW_KEY_E},
    {eKeyboardKey_F, GLFW_KEY_F},
    {eKeyboardKey_G, GLFW_KEY_G},
    {eKeyboardKey_H, GLFW_KEY_H},
    {eKeyboardKey_I, GLFW_KEY_I},
    {eKeyboardKey_J, GLFW_KEY_J},
    {eKeyboardKey_K, GLFW_KEY_K},
    {eKeyboardKey_L, GLFW_KEY_L},
    {eKeyboardKey_M, GLFW_KEY_M},
    {eKeyboardKey_N, GLFW_KEY_N},
    {eKeyboardKey_O, GLFW_KEY_O},
    {eKeyboardKey_P, GLFW_KEY_P},
    {eKeyboardKey_Q, GLFW_KEY_Q},
    {eKeyboardKey_R, GLFW_KEY_R},
    {eKeyboardKey_S, GLFW_KEY_S},
    {eKeyboardKey_T, GLFW_KEY_T},
    {eKeyboardKey_U, GLFW_KEY_U},
    {eKeyboardKey_V, GLFW_KEY_V},
    {eKeyboardKey_W, GLFW_KEY_W},
    {eKeyboardKey_X, GLFW_KEY_X},
    {eKeyboardKey_Y, GLFW_KEY_Y},
    {eKeyboardKey_Z, GLFW_KEY_Z},
    {eKeyboardKey_Space, GLFW_KEY_SPACE},
    {eKeyboardKey_Alpha0, GLFW_KEY_0},
    {eKeyboardKey_Alpha1, GLFW_KEY_1},
    {eKeyboardKey_Alpha2, GLFW_KEY_2},
    {eKeyboardKey_Alpha3, GLFW_KEY_3},
    {eKeyboardKey_Alpha4, GLFW_KEY_4},
    {eKeyboardKey_Alpha5, GLFW_KEY_5},
    {eKeyboardKey_Alpha6, GLFW_KEY_6},
    {eKeyboardKey_Alpha7, GLFW_KEY_7},
    {eKeyboardKey_Alpha8, GLFW_KEY_8},
    {eKeyboardKey_Alpha9, GLFW_KEY_9},
    {eKeyboardKey_Pad0, GLFW_KEY_KP_0},
    {eKeyboardKey_Pad1, GLFW_KEY_KP_1},
    {eKeyboardKey_Pad2, GLFW_KEY_KP_2},
    {eKeyboardKey_Pad3, GLFW_KEY_KP_3},
    {eKeyboardKey_Pad4, GLFW_KEY_KP_4},
    {eKeyboardKey_Pad5, GLFW_KEY_KP_5},
    {eKeyboardKey_Pad6, GLFW_KEY_KP_6},
    {eKeyboardKey_Pad7, GLFW_KEY_KP_7},
    {eKeyboardKey_Pad8, GLFW_KEY_KP_8},
    {eKeyboardKey_Pad9, GLFW_KEY_KP_9},

};

stde::bimap<eMouseButton, int> LumedaGLFWMouseButtonMapping = {{}};

///////////////////////////////////////////
// Constructor
///////////////////////////////////////////

InputsGL::InputsGL(LowLevelGraphicsGL& lowLevelGraphics, Timer& timer) : iInputs("InputsGL"), m_LowLevelGraphics(lowLevelGraphics), m_Timer(timer)
{
  m_LowLevelGraphics.GetGLFWWindowUserData().inputsGL = this;

  for (eKeyboardKey i = eKeyboardKey_FirstEnum; i < eKeyboardKey_LastEnum; i = (eKeyboardKey)(i + 1))
  {
    m_KeyboardState[i].framecount = m_Timer.GetFrameCount();
    m_KeyboardState[i].state = eKeyboardKeyState_Up;
  }

  GLFWwindow* windowHandle = m_LowLevelGraphics.GetOpenGLWindow();
  glfwSetKeyCallback(windowHandle, OnKeyCallback);

  LUMEDA_CORE_INFO("[InputsGL] Init");
}

InputsGL::~InputsGL()
{
  GLFWwindow* windowHandle = m_LowLevelGraphics.GetOpenGLWindow();
  glfwSetKeyCallback(windowHandle, nullptr);
}

///////////////////////////////////////////
// Keyboard
///////////////////////////////////////////
eKeyboardKeyState InputsGL::GetKey(eKeyboardKey key)
{
  sKeyboardKeyState& state = m_KeyboardState[key];
  size_t currentFramecount = m_Timer.GetFrameCount();

  // Check when we want to get a Key if the state should change.
  if (state.state == eKeyboardKeyState_Press)
  {
    if (currentFramecount > state.framecount)
    {
      state.state = eKeyboardKeyState_Down;
      state.framecount = currentFramecount;
    }
  }
  else if (state.state == eKeyboardKeyState_Release)
  {
    if (currentFramecount > state.framecount)
    {
      state.state = eKeyboardKeyState_Up;
      state.framecount = currentFramecount;
    }
  }

  return state.state;
}

///////////////////////////////////////////
// Mouse
///////////////////////////////////////////
eMouseButtonState InputsGL::GetMouseButton(eMouseButton button)
{
  return eMouseButtonState_Down;
}

///////////////////////////////////////////
// Callback
///////////////////////////////////////////
void InputsGL::OnKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
  InputsGL* inputs = static_cast<sGLFWWindowUserData*>(glfwGetWindowUserPointer(window))->inputsGL;
  inputs->OnKey(key, scanCode, action, mods);
}

void InputsGL::OnKey(int GLFWKey, int GLFWScanCode, int GLFWAction, int GLFWMods)
{
  eKeyboardKey key = GLFWKeyToLumeda(GLFWKey);

  if (GLFWAction == GLFW_PRESS)
  {
    m_KeyboardState[key].framecount = m_Timer.GetFrameCount();
    m_KeyboardState[key].state = eKeyboardKeyState_Press;
  }
  else if (GLFWAction == GLFW_RELEASE)
  {
    m_KeyboardState[key].framecount = m_Timer.GetFrameCount();
    m_KeyboardState[key].state = eKeyboardKeyState_Release;
  }
}

///////////////////////////////////////////
// General functions
///////////////////////////////////////////

int Lumeda::LumedaKeyToGLFW(eKeyboardKey key)
{
  if (!LumedaGLFWKeyboardKeyMapping.has_key(key))
  {
    LUMEDA_CORE_WARN("[InputsGL] Lumeda key '{0}' has no mapping", (int)key);
    return GLFW_KEY_A;
  }
  return LumedaGLFWKeyboardKeyMapping.get_value(key);
}

int Lumeda::LumedaMouseButtonGLFW(eMouseButton button)
{
  if (!LumedaGLFWMouseButtonMapping.has_key(button))
  {
    LUMEDA_CORE_WARN("[InputsGL] Lumeda button '{0}' has no mapping", (int)button);
    return GLFW_MOUSE_BUTTON_LEFT;
  }
  return LumedaGLFWMouseButtonMapping.get_value(button);
}

eKeyboardKey Lumeda::GLFWKeyToLumeda(int key)
{
  if (!LumedaGLFWKeyboardKeyMapping.has_value(key))
  {
    LUMEDA_CORE_WARN("[InputsGL] GLFW key '{0}' has no mapping", key);
    return eKeyboardKey_A;
  }
  return LumedaGLFWKeyboardKeyMapping.get_key(key);
}

eMouseButton Lumeda::GLFWMouseButtonToLumeda(int button)
{
  if (!LumedaGLFWMouseButtonMapping.has_value(button))
  {
    LUMEDA_CORE_WARN("[InputsGL] GLFW button '{0}' has no mapping", button);
    return eMouseButton_Left;
  }
  return LumedaGLFWMouseButtonMapping.get_key(button);
}