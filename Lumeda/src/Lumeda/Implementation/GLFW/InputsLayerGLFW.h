#include <Lumeda/Core/Base.h>

#include <Lumeda/Core/InputsLayer.h>

#include <GLFW/glfw3.h>

namespace Lumeda
{
class InputsLayerGLFW : public InputsLayer
{
public:
	InputsLayerGLFW();
	virtual ~InputsLayerGLFW();

	void Initialize() override;
	void Update() override;
	void Terminate() override;

	bool IsKeyPressed(LumedaKeys key) override;
	bool IsKeyDown(LumedaKeys key) override;
	bool IsKeyUp(LumedaKeys key) override;

	bool IsMouseButtonPressed(LumedaMouseButtons button) override;
	bool IsMouseButtonDown(LumedaMouseButtons button) override;
	bool IsMouseButtonUp(LumedaMouseButtons button) override;

protected:
	GLFWwindow* m_nativeWindow;
};
}