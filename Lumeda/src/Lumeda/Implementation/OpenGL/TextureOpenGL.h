#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Texture.h>

#include <string>

namespace Lumeda
{
	class Texture2DOpenGL : public Texture2D
	{
	public:
		Texture2DOpenGL(const std::string& name, const std::string& path);
		virtual ~Texture2DOpenGL();

		void Bind(int slot = 0) override;
		void UnBind() override;

		void SetFiltering(TextureFiltering filtering) override;

		int GetWidth() const override;
		int GetHeight() const override;

		const std::string& GetName() const override
		{
			return m_Name;
		}

	private:
		unsigned int m_Handle;
		std::string m_Name;

		int m_Width;
		int m_Height;
	};
}