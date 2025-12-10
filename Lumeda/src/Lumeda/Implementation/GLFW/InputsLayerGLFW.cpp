#include <Lumeda/Implementation/GLFW/InputsLayerGLFW.h>
#include <Lumeda/Implementation/GLFW/WindowGLFW.h>
#include <Lumeda/Core/Engine.h>

#include <GLFW/glfw3.h>

using namespace Lumeda;

InputsLayerGLFW::InputsLayerGLFW() : m_nativeWindow()
{
	LUMEDA_PROFILE;
	// The inputs layer is created AFTER the window
	WindowGLFW* window = static_cast<WindowGLFW*>(&Engine::Get().GetWindow());
	m_nativeWindow = window->GetNativeGLFWWindow();
}

InputsLayerGLFW::~InputsLayerGLFW()
{
	LUMEDA_PROFILE;
}

void InputsLayerGLFW::Update()
{
	LUMEDA_PROFILE;
}

void InputsLayerGLFW::Initialize()
{
	LUMEDA_PROFILE;
}

void InputsLayer::Update()
{
	LUMEDA_PROFILE;
}

void InputsLayerGLFW::Terminate()
{
	LUMEDA_PROFILE;
}

bool InputsLayerGLFW::IsKeyPressed(LumedaKeys key)
{
	LUMEDA_PROFILE;
	return glfwGetKey(m_nativeWindow, key) == GLFW_PRESS;
}

bool InputsLayerGLFW::IsKeyDown(LumedaKeys key)
{
	LUMEDA_PROFILE;
	return glfwGetKey(m_nativeWindow, key) == GLFW_PRESS;
}

bool InputsLayerGLFW::IsKeyUp(LumedaKeys key)
{
	LUMEDA_PROFILE;
	return glfwGetKey(m_nativeWindow, key) == GLFW_RELEASE;
}

bool InputsLayerGLFW::IsMouseButtonPressed(LumedaMouseButtons button)
{
	LUMEDA_PROFILE;
	return glfwGetMouseButton(m_nativeWindow, button) == GLFW_PRESS;
}

bool InputsLayerGLFW::IsMouseButtonDown(LumedaMouseButtons button)
{
	LUMEDA_PROFILE;
	return glfwGetMouseButton(m_nativeWindow, button) == GLFW_PRESS;
}

bool InputsLayerGLFW::IsMouseButtonUp(LumedaMouseButtons button)
{
	LUMEDA_PROFILE;
	return glfwGetMouseButton(m_nativeWindow, button) == GLFW_RELEASE;
}
