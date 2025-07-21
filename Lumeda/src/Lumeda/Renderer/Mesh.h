#pragma once

#include <Lumeda/Core/Base.h>

#include <variant>

namespace Lumeda
{
	enum class MeshAttribType
	{
		INT,
		FLOAT
	};

	struct MeshAttrib
	{
		int Index;
		int Count;
		MeshAttribType Type;

		MeshAttrib(int index, int count, MeshAttribType type) : Index(index), Count(count), Type(type)
		{ }
	};

	class Mesh
	{
	public:
		virtual ~Mesh() = default;

		virtual void Draw() = 0;

		virtual const std::string& GetName() const = 0;
	};

}