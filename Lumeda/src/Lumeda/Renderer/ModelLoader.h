#pragma once

#include <Lumeda/Renderer/Model.h>

namespace Lumeda
{
	class ModelLoader
	{
	public:
		static void LoadModelFromFile(std::shared_ptr<Model> model, const std::string& path);
	};
}