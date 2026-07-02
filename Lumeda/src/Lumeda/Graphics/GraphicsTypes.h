#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/EngineTypes.h>

namespace Lumeda
{
typedef glm::vec4 tColor;

///////////////////////////////////////////
// Events
///////////////////////////////////////////
enum eGraphicsEvent
{
  eGraphicsEvent_FirstEnum = eEventCategory_Graphics,

  eGraphicsEvent_WindowShouldClose,
  eGraphicsEvent_WindowResize,
  eGraphicsEvent_WindowFrameBufferSize,
  eGraphicsEvent_WindowFocus,
  eGraphicsEvent_WindowPosition,

  eGraphicsEvent_LastEnum,
};

class WindowShouldCloseEvent : public iEvent
{
public:
  WindowShouldCloseEvent() {}

  tEventType GetType() { return eGraphicsEvent_WindowShouldClose; }
};

class WindowResizeEvent : public iEvent
{
public:
  WindowResizeEvent(int width, int height) : Width(width), Height(height) {}

  tEventType GetType() { return eGraphicsEvent_WindowResize; }

  int Width, Height;
};

class WindowFrameBufferSizeEvent : public iEvent
{
public:
  WindowFrameBufferSizeEvent(int width, int height) : Width(width), Height(height) {}

  tEventType GetType() { return eGraphicsEvent_WindowFrameBufferSize; }

  int Width, Height;
};

class WindowFocusEvent : public iEvent
{
public:
  WindowFocusEvent(bool focus) : Focus(focus) {}

  tEventType GetType() { return eGraphicsEvent_WindowFocus; }

  bool Focus;
};

class WindowPositionEvent : public iEvent
{
public:
  WindowPositionEvent(int x, int y) : X(x), Y(y) {}

  tEventType GetType() { return eGraphicsEvent_WindowPosition; }

  int X, Y;
};
//---------------------------------------//

///////////////////////////////////////////
// FrameBuffer
///////////////////////////////////////////
typedef tFlag tClearFrameBufferFlag;

#define tClearFrameBufferFlag_Color (1)
#define tClearFrameBufferFlag_Depth (2)
#define tClearFrameBufferFlag_Stencil (4)

enum eFrameBufferAttachment
{
  eFrameBufferAttachment_Color,
  eFrameBufferAttachment_Depth,
  eFrameBufferAttachment_Stencil,
  eFrameBufferAttachment_DepthStencil
};
//---------------------------------------//

///////////////////////////////////////////
// Textures
///////////////////////////////////////////
enum ePixelFormat
{
  ePixelFormat_RGB,
  ePixelFormat_RGBA
};

enum eTextureFiltering
{
  eTextureFiltering_Nearest,
  eTextureFiltering_Linear
};

enum eTextureWrapping
{
  eTextureWrapping_Repeat,
  eTextureWrapping_Clamp
};

enum eTextureFormat
{
  eTextureFormat_RGB,
  eTextureFormat_DepthStencil
};

enum eTextureType
{
  eTextureType_1D,
  eTextureType_2D,
  eTextureType_3D
};

enum eTextureUsage
{
  eTextureUsage_Normal,
  eTextureUsage_RenderTarget,
  eTextureUsage_LastEnum
};
//---------------------------------------//

///////////////////////////////////////////
// Shaders
///////////////////////////////////////////

enum eShaderType
{
  eShaderType_Vertex,
  eShaderType_Fragment,
  eShaderType_Geometry,
  eShaderType_LastEnum
};

//---------------------------------------//

///////////////////////////////////////////
// Vertex Array
///////////////////////////////////////////

enum eVertexAttribType
{
  eVertexAttribType_Float,
  eVertexAttribType_LastEnum
};

struct sVertexArrayAttrib
{
  int location;
  int length;
  eVertexAttribType type;
};

//---------------------------------------//

} // namespace Lumeda