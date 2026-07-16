#pragma once

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
  virtual bool isKeyPress(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Press; }
  virtual bool isKeyDown(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Down; }
  virtual bool isKeyRelease(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Release; }
  virtual bool isKeyUp(eKeyboardKey key) { return GetKey(key) == eKeyboardKeyState_Up; }

  ///////////////////////////////////////////
  // Mouse
  ///////////////////////////////////////////
  virtual eMouseButtonState GetMouseButton(eMouseButton button) = 0;
  virtual bool isMouseButtonPress(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Pressed; }
  virtual bool isMouseButtonDown(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Down; }
  virtual bool isMouseButtonRelease(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Release; }
  virtual bool isMouseButtonUp(eMouseButton button) { return GetMouseButton(button) == eMouseButtonState_Up; }
};
} // namespace Lumeda