#pragma once

#include <Lumeda/Renderer/Shader.h>

namespace Lumeda
{
	class ShaderOpenGL : public Shader
	{
	public:
		ShaderOpenGL(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~ShaderOpenGL();

		void Bind() override;
		void UnBind() override;

		void SetUniform(const std::string& uniform, int value) override;
		void SetUniform(const std::string& uniform, float value) override;
		void SetUniform(const std::string& uniform, const glm::vec2& value) override;
		void SetUniform(const std::string& uniform, const glm::vec3& value) override;
		void SetUniform(const std::string& uniform, const glm::vec4& value) override;
		void SetUniform(const std::string& uniform, const glm::mat2& value) override;
		void SetUniform(const std::string& uniform, const glm::mat3& value) override;
		void SetUniform(const std::string& uniform, const glm::mat4& value) override;


		const std::string& GetName() const override { return m_Name; }

	private:
		std::string m_VertexPath;
		std::string m_FragmentPath;
		unsigned int m_Handle;
		
		std::string m_Name;
	};
}