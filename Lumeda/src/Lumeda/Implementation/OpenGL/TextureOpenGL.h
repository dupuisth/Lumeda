#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Texture.h>

#include <string>
#include <glm/glm.hpp>

namespace Lumeda
{
	class Texture2DOpenGL : public Texture2D
	{
	public:
		Texture2DOpenGL(const std::string& name, const std::string& path);
		Texture2DOpenGL(const std::string& name, int width, int height, eTextureFormat format);
		virtual ~Texture2DOpenGL();

		void Bind(int slot = 0) override;
		void UnBind() override;

		eTextureWrapping GetWrapping() const override;
		void SetWrapping(eTextureWrapping wrapping) override;

		eTextureFiltering GetFiltering() const override;
		void SetFiltering(eTextureFiltering filtering) override;

		void Build(int width, int height, eTextureFormat format);

		const glm::ivec2& GetSize() const override;
		int GetWidth() const override;
		int GetHeight() const override;

		const std::string& GetName() const override;

		unsigned int GetOpenGLHandle();

	private:
		unsigned int m_Handle;
		std::string m_Name;

		glm::ivec2 m_Size;

		eTextureFiltering m_Filtering;
		eTextureWrapping m_Wrapping;
	};
}