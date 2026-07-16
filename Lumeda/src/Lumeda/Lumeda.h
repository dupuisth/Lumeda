#pragma once

///////////////////////////////////////////
// Core
///////////////////////////////////////////
#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Log.h>

///////////////////////////////////////////
// Engine
///////////////////////////////////////////
#include <Lumeda/Engine/Engine.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Engine/EventManager.h>
#include <Lumeda/Engine/EventReceiver.h>
#include <Lumeda/Engine/LowLevelEngineSetup.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Engine/Updater.h>

///////////////////////////////////////////
// Graphics
///////////////////////////////////////////
#include <Lumeda/Graphics/FrameBuffer.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GpuShader.h>
#include <Lumeda/Graphics/Graphics.h>
#include <Lumeda/Graphics/GraphicsTypes.h>
#include <Lumeda/Graphics/LowLevelGraphics.h>
#include <Lumeda/Graphics/RenderBuffer.h>
#include <Lumeda/Graphics/Renderer.h>
#include <Lumeda/Graphics/SimpleRenderer.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Graphics/VertexBuffer.h>

///////////////////////////////////////////
// Resources
///////////////////////////////////////////
#include <Lumeda/Resources/GpuProgramManager.h>
#include <Lumeda/Resources/GpuShaderManager.h>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Resources/ModelManager.h>
#include <Lumeda/Resources/ResourceBase.h>
#include <Lumeda/Resources/ResourceManager.h>
#include <Lumeda/Resources/Resources.h>
#include <Lumeda/Resources/TextureManager.h>

///////////////////////////////////////////
// Scene
///////////////////////////////////////////
#include <Lumeda/Scene/Camera.h>
#include <Lumeda/Scene/CameraEntity.h>
#include <Lumeda/Scene/Entity.h>
#include <Lumeda/Scene/LeafNode.h>
#include <Lumeda/Scene/MeshEntity.h>
#include <Lumeda/Scene/ModelEntity.h>
#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/Renderable.h>
#include <Lumeda/Scene/Viewport.h>
#include <Lumeda/Scene/World.h>

///////////////////////////////////////////
// Inputs
///////////////////////////////////////////
#include <Lumeda/Inputs/Inputs.h>
#include <Lumeda/Inputs/InputsTypes.h>

///////////////////////////////////////////
// ImGui
///////////////////////////////////////////
#include <Lumeda/ImGui/ImGuiLayer.h>