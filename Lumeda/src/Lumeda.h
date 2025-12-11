#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Engine.h>
#include <Lumeda/Core/Log.h>
#include <Lumeda/Core/Window.h>
#include <Lumeda/Core/Layer.h>

#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/Texture.h>
#include <Lumeda/Renderer/Mesh.h>
#include <Lumeda/Renderer/Camera.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/Model.h>
#include <Lumeda/Renderer/Light.h>

#include <Lumeda/Node/Node.h>
#include <Lumeda/Node/RootNode.h>
#include <Lumeda/Node/ModelNode.h>
#include <Lumeda/Node/SpinNode.h>
#include <Lumeda/Node/PlayerNode.h>
#include <Lumeda/Node/CameraNode.h>
#include <Lumeda/Node/LightNode.h>

#ifdef LUMEDA_USE_GLFW
#include <Lumeda/Implementation/GLFW/WindowGLFW.h>
#endif

#ifdef LUMEDA_USE_GLAD
#include <Lumeda/Implementation/OpenGL/MeshOpenGL.h>
#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>
#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#endif