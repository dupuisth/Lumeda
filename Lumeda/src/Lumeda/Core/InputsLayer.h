#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Core/Layer.h>

namespace Lumeda
{
class InputsLayer : public Layer
{
public:
	void Initialize() override;
	void Terminate() override;
};
}