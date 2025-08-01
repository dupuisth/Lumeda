#pragma once

#include <Lumeda/Core/Base.h>

#include <vector>

namespace Lumeda
{
	template <typename T>
	struct TickVector
	{
		std::vector<T> Create;
		std::vector<T> Current;
		std::vector<T> Destroy;
	};
}