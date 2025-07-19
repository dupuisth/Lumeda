#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
	enum TextureFiltering
	{
		Nearest,
		Linear
	};

	class Texture
	{
	public:
		virtual void Bind(int slot = 0) = 0;
		virtual void UnBind() = 0;

		virtual void SetFiltering(TextureFiltering filtering) = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual const std::string& GetName() const = 0;
	};

	class Texture2D : public Texture
	{

	};
}