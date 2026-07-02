#pragma once

#include <glm/glm.hpp>
#include <Lumeda/Core/Base.h>

namespace Lumeda
{
typedef glm::vec4 tColor;

///////////////////////////////////////////
// FrameBuffer
///////////////////////////////////////////
typedef tFlag tClearFrameBufferFlag;

#define tClearFrameBufferFlag_Color (0x1)
#define tClearFrameBufferFlag_Depth (0x2)
#define tClearFrameBufferFlag_Stencil (0x4)

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