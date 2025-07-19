#pragma once

#include <Lumeda/Core/Base.h>

#include <string>

namespace Lumeda
{
	class FileReader
	{
	public:
		static std::string ReadFile(const std::string& filepath);
	};
}