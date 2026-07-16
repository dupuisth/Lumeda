#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

///////////////////////////////////////////
// Keys
///////////////////////////////////////////

enum eKeyboardKey
{
  eKeyboardKey_FirstEnum = 0,
  eKeyboardKey_A,
  eKeyboardKey_B,
  eKeyboardKey_C,
  eKeyboardKey_D,
  eKeyboardKey_E,
  eKeyboardKey_F,
  eKeyboardKey_G,
  eKeyboardKey_H,
  eKeyboardKey_I,
  eKeyboardKey_J,
  eKeyboardKey_K,
  eKeyboardKey_L,
  eKeyboardKey_M,
  eKeyboardKey_N,
  eKeyboardKey_O,
  eKeyboardKey_P,
  eKeyboardKey_Q,
  eKeyboardKey_R,
  eKeyboardKey_S,
  eKeyboardKey_T,
  eKeyboardKey_U,
  eKeyboardKey_V,
  eKeyboardKey_W,
  eKeyboardKey_X,
  eKeyboardKey_Y,
  eKeyboardKey_Z,

  eKeyboardKey_Space,

  eKeyboardKey_Alpha0,
  eKeyboardKey_Alpha1,
  eKeyboardKey_Alpha2,
  eKeyboardKey_Alpha3,
  eKeyboardKey_Alpha4,
  eKeyboardKey_Alpha5,
  eKeyboardKey_Alpha6,
  eKeyboardKey_Alpha7,
  eKeyboardKey_Alpha8,
  eKeyboardKey_Alpha9,

  eKeyboardKey_Pad0,
  eKeyboardKey_Pad1,
  eKeyboardKey_Pad2,
  eKeyboardKey_Pad3,
  eKeyboardKey_Pad4,
  eKeyboardKey_Pad5,
  eKeyboardKey_Pad6,
  eKeyboardKey_Pad7,
  eKeyboardKey_Pad8,
  eKeyboardKey_Pad9,

  eKeyboardKey_LastEnum,
};

enum eKeyboardKeyState
{
  eKeyboardKeyState_Press,
  eKeyboardKeyState_Down,
  eKeyboardKeyState_Release,
  eKeyboardKeyState_Up,
};

///////////////////////////////////////////
// Mouse
///////////////////////////////////////////

enum eMouseButton
{
  eMouseButton_Left,
  eMouseButton_Middle,
  eMouseButton_Right,
};

enum eMouseButtonState
{
  eMouseButtonState_Pressed,
  eMouseButtonState_Down,
  eMouseButtonState_Release,
  eMouseButtonState_Up,
};

} // namespace Lumeda