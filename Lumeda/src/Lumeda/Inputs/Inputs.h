#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Inputs/InputsTypes.h>
namespace Lumeda
{
class iInputs : public iUpdateable
{
public:
  iInputs(const tString& name) : iUpdateable(name) {}
  ~iInputs() = default;

  ///////////////////////////////////////////
  // Keyboard
  ///////////////////////////////////////////
  virtual eKeyboardKeyState GetKey(eKeyboardKey key) = 0;
  virtual bool IsKeyPress(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Press; }
  virtual bool IsKeyDown(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Down; }
  virtual bool IsKeyRelease(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Release; }
  virtual bool IsKeyUp(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Up; }

  ///////////////////////////////////////////
  // Mouse
  ///////////////////////////////////////////
  virtual eMouseButtonState GetMouseButton(eMouseButton button) = 0;
  virtual bool IsMouseButtonPress(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Press; }
  virtual bool IsMouseButtonDown(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Down; }
  virtual bool IsMouseButtonRelease(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Release; }
  virtual bool IsMouseButtonUp(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Up; }

  virtual glm::vec2 GetMouseDelta() = 0;
  virtual glm::vec2 GetMouseScreenPosition() = 0;

  ///////////////////////////////////////////
  // Cursor
  ///////////////////////////////////////////
  virtual void SetCursorMode(eCursorMode mode) = 0;
};
} // namespace Lumeda