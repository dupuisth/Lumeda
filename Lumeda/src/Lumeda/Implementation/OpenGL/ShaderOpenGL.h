#pragma once

#include <Lumeda/Renderer/Shader.h>

namespace Lumeda
{
	class ShaderOpenGL : public Shader
	{
	public:
		ShaderOpenGL(const std::string& vertexPath, const std::string& fragmentPath);
		~ShaderOpenGL();

		void Bind() override;
		void UnBind() override;

		void SetFloat(const std::string& uniform, float value) override;
		void SetInt(const std::string& uniform, int value) override;

	private:
		std::string m_VertexPath;
		std::string m_FragmentPath;
		unsigned int m_Handle;
	};
}