#pragma once

#include <string>

namespace Lumeda
{
	class Shader
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void SetFloat(const std::string& uniform, float value) = 0;
		virtual void SetInt(const std::string& uniform, int value) = 0;

		virtual const std::string& GetName() const = 0;
	};
}