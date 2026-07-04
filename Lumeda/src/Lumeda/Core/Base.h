#pragma once

#include <memory>
#include <Lumeda/Core/Assert.h>
#include <Lumeda/Core/Log.h>
#include <Lumeda/Engine/EngineTypes.h>

#define LUMEDA_RANDINT(a, b) ((a) + (int)((double)rand() / (RAND_MAX + 1.0) * ((b) - (a))))
#define LUMEDA_RANDFLOAT(a, b) (((float)rand() / (float)(RAND_MAX)) * (b - a) + a)

#if !defined(LUMEDA_PROFILING)
#define LUMEDA_PROFILE
#define LUMEDA_PROFILE_FRAME
#define LUMEDA_PROFILE_SECTION(x)
#define LUMEDA_PROFILE_TAG(x)
#define LUMEDA_PROFILE_LOG(text, size)
#define LUMEDA_PROFILE_VALUE(text, value)
#define LUMEDA_PROFILE_MEMORY_ALLOC(p, size)
#define LUMEDA_PROFILE_MEMORY_FREE(p)

#else

#define TRACY_ENABLE
#include <tracy/Tracy.hpp>
#define LUMEDA_PROFILING_ENABLED
#define LUMEDA_PROFILE ZoneScoped
#define LUMEDA_PROFILE_FRAME FrameMark
#define LUMEDA_PROFILE_SECTION(x) ZoneScopedN(x)
// #define LUMEDA_PROFILE_TAG(x) ZoneText(x, strlen(x))
#define LUMEDA_PROFILE_TAG(x) ZoneScoped
#define LUMEDA_PROFILE_LOG(text, size) TracyMessage(text, size)
#define LUMEDA_PROFILE_VALUE(text, value) TracyPlot(text, value)
#define LUMEDA_PROFILE_MEMORY_ALLOC(p, size) TracyAlloc(p, size);
#define LUMEDA_PROFILE_MEMORY_FREE(p) TracyFree(p);
#endif

#if defined(LUMEDA_PLATFORM_LINUX) || defined(LUMEDA_PLATFORM_WINDOWS)
#define LUMEDA_USE_GLFW
#define LUMEDA_USE_GLAD
#endif

// Keycodes
#ifdef LUMEDA_USE_GLFW
// Define the keycodes using the GLFW values
// https://www.glfw.org/docs/3.3/group__keys.html
enum LumedaKeys // There are some missing keys, will be added when needed
{
  LUMEDA_KEY_A = 65,
  LUMEDA_KEY_B,
  LUMEDA_KEY_C,
  LUMEDA_KEY_D,
  LUMEDA_KEY_E,
  LUMEDA_KEY_F,
  LUMEDA_KEY_G,
  LUMEDA_KEY_H,
  LUMEDA_KEY_I,
  LUMEDA_KEY_J,
  LUMEDA_KEY_K,
  LUMEDA_KEY_L,
  LUMEDA_KEY_M,
  LUMEDA_KEY_N,
  LUMEDA_KEY_O,
  LUMEDA_KEY_P,
  LUMEDA_KEY_Q,
  LUMEDA_KEY_R,
  LUMEDA_KEY_S,
  LUMEDA_KEY_T,
  LUMEDA_KEY_U,
  LUMEDA_KEY_V,
  LUMEDA_KEY_W,
  LUMEDA_KEY_X,
  LUMEDA_KEY_Y,
  LUMEDA_KEY_Z,

  LUMEDA_KEY_0 = 48,
  LUMEDA_KEY_1,
  LUMEDA_KEY_2,
  LUMEDA_KEY_3,
  LUMEDA_KEY_4,
  LUMEDA_KEY_5,
  LUMEDA_KEY_6,
  LUMEDA_KEY_7,
  LUMEDA_KEY_8,
  LUMEDA_KEY_9,

  LUMEDA_KEY_F1 = 290,
  LUMEDA_KEY_F2,
  LUMEDA_KEY_F3,
  LUMEDA_KEY_F4,
  LUMEDA_KEY_F5,
  LUMEDA_KEY_F6,
  LUMEDA_KEY_F7,
  LUMEDA_KEY_F8,
  LUMEDA_KEY_F9,
  LUMEDA_KEY_F10,
  LUMEDA_KEY_F11,
  LUMEDA_KEY_F12,

  LUMEDA_KEY_SPACE = 32,
};

enum LumedaMouseButtons
{
  LUMEDA_MOUSE_LEFT = 0,
  LUMEDA_MOUSE_RIGHT,
  LUMEDA_MOUSE_MIDDLE,
};

#else
#error "Undefined platform!"
#endif
