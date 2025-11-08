#pragma once

#include <Lumeda/Node/Node.h>

namespace Lumeda
{
class PlayerNode : public Node
{
	PlayerNode();
	virtual ~PlayerNode();

	void OnUpdate() override;
	void OnRender() override;
	void OnRenderImGui() override;
};
}