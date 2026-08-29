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

  tString ToString() { return "WindowShouldClose"; }
};

class WindowResizeEvent : public iEvent
{
public:
  WindowResizeEvent(int width, int height) : Width(width), Height(height) {}

  tEventType GetType() { return eGraphicsEvent_WindowResize; }

  tString ToString() { return "WindowResizeEvent(width: " + std::to_string(Width) + ", height: " + std::to_string(Height) + ")"; }

  int Width, Height;
};

class WindowFrameBufferSizeEvent : public iEvent
{
public:
  WindowFrameBufferSizeEvent(int width, int height) : Width(width), Height(height) {}

  tEventType GetType() { return eGraphicsEvent_WindowFrameBufferSize; }

  tString ToString() { return "WindowFrameBufferSizeEvent(width: " + std::to_string(Width) + ", height: " + std::to_string(Height) + ")"; }

  int Width, Height;
};

class WindowFocusEvent : public iEvent
{
public:
  WindowFocusEvent(bool focus) : Focus(focus) {}

  tEventType GetType() { return eGraphicsEvent_WindowFocus; }

  tString ToString() { return "WindowFocusEvent(" + std::to_string(Focus) + ")"; }

  bool Focus;
};

class WindowPositionEvent : public iEvent
{
public:
  WindowPositionEvent(int x, int y) : X(x), Y(y) {}

  tEventType GetType() { return eGraphicsEvent_WindowPosition; }

  tString ToString() { return "WindowPositionEvent(x: " + std::to_string(X) + ", y: " + std::to_string(Y) + ")"; }

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
  eFrameBufferAttachment_Color = 0,
  eFrameBufferAttachment_Depth,
  eFrameBufferAttachment_Stencil,
  eFrameBufferAttachment_DepthStencil,
  eFrameBufferAttachment_LastValue
};
//---------------------------------------//

///////////////////////////////////////////
// Textures
///////////////////////////////////////////
enum ePixelFormat
{
  ePixelFormat_RGB,
  ePixelFormat_RGBA,
  ePixelFormat_Depth16,
  ePixelFormat_Depth24,
  ePixelFormat_Depth32,
  ePixelFormat_Depth24Stencil8,
  ePixelFormat_LastEnum,
};

enum eTextureFiltering
{
  eTextureFiltering_Nearest = 0,
  eTextureFiltering_Linear
};

enum eTextureWrapping
{
  eTextureWrapping_Repeat = 0,
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
  eTextureUsage_RenderBuffer,
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

// Changing order will brake the MaterialXML
enum eShaderUniformType
{
  eShaderUniformType_Float = 0,
  eShaderUniformType_Vec2,
  eShaderUniformType_Vec3,
  eShaderUniformType_Vec4,
  eShaderUniformType_Texture2D,
  eShaderUniformType_LastEnum,
};

#define tShaderCommonUniform_CameraMatrix "u_Camera"
#define tShaderCommonUniform_CameraProject "u_CameraProj"
#define tShaderCommonUniform_CameraView "u_CameraView"
#define tShaderCommonUniform_CameraPosition "u_CameraPosition"
#define tShaderCommonUniform_CameraForward "u_CameraForward"

#define tShaderCommonUniform_ObjectWorld "u_World"
#define tShaderCommonUniform_ObjectLocalPosition "u_LocalPosition"
#define tShaderCommonUniform_ObjectLocalRotation "u_LocalRotation"
#define tShaderCommonUniform_ObjectLocalScale "u_LocalScale"
#define tShaderCommonUniform_ObjectPosition "u_Position"
#define tShaderCommonUniform_ObjectRotation "u_Rotation"
#define tShaderCommonUniform_ObjectScale "u_Scale"

#define tShaderCommonUniform_TextureDiffuse0 "u_DiffuseTexture0"
#define tShaderCommonUniform_TextureNormal0 "u_NormalTexture0"

#define tShaderCommonUniform_MainDirectionalLight "u_DirectionalLight"
#define tShaderCommonUniform_StructDirectionalLight_Direction "Direction"
#define tShaderCommonUniform_StructDirectionalLight_Color "Color"

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

///////////////////////////////////////////
// Draw mode
///////////////////////////////////////////

enum ePolygonMode
{
  ePolygonMode_Point,
  ePolygonMode_Line,
  ePolygonMode_Fill
};

enum ePolygonFace
{
  ePolygonFace_Front,
  ePolygonFace_Back,
  ePolygonFace_FrontBack,
};
//---------------------------------------//

} // namespace Lumeda